#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"
#include "EmptyPiece.h"
#include <windows.h>   // WinApi header

string Board::getLocation(int index)
{
	// calculate row and col by the index
	int row = index / BOARD_SIZE;
	int col = index % BOARD_SIZE;

	// BOARD_SIZE - row because we start from top
	return string(1, col + 'a') + (char)((BOARD_SIZE - row) + '0');
}

string Board::getLocation(int row, int col)
{
	return getLocation(getIndex(row, col));
}

void Board::printAllValidLocations(Piece& src)
{
	Piece* dest;
	int i = 0, j = 0;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			dest = getPiece(getLocation(i, j));

			// if its the src, then print it in red
			if (dest->getLocation() == src.getLocation())
			{
				std::cout << "\033[0;31m" << *dest << "\033[0m";
			}
			else
			{
				// make basic checks, if all basic checks passed, make
				// further checks with the current piece, and send result to graphics
				int result = src.basicValidateMove(getCurrentPlayer(), *dest);
				if (result == VALID_MOVE) result = src.validateMove(*dest);
				if (result == VALID_MOVE)
				{
					// all valid moves should be printed in green (or blue if its a capture move)
					std::cout << (dest->getType() == EMPTY_PIECE ? "\033[0;32m" : "\033[0;34m") << *dest << "\033[0m";
				}
				else
				{
					std::cout << *dest;
				}
			}
			delete dest; // free Piece's memory after use
			std::cout << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int Board::getIndex(const string& location)
{
	return getIndex(BOARD_SIZE - (location[1] - '0'), location[0] - 'a');
}

int Board::getIndex(const int row, const int col)
{
	return row * BOARD_SIZE + col;
}

Board::Board(const string& board)
{
	// initiate our 2 players's objects
	_players[WHITE_PLAYER] = new Player(this, WHITE_PLAYER);
	_players[BLACK_PLAYER] = new Player(this, BLACK_PLAYER);

	// last char is which player is starting
	_currentPlayer = board[BOARD_SIZE * BOARD_SIZE] - '0';
	_board = board;
	_board.pop_back(); // remove the starting player char
}

Board::~Board()
{
	// free the memory of our players
	delete _players[WHITE_PLAYER];
	delete _players[BLACK_PLAYER];

	// clear board's string
	_board.clear();
}

string& Board::getBoard()
{
	return _board;
}

Player** Board::getPlayers()
{
	return _players;
}

Player& Board::getCurrentPlayer() const
{
	return *_players[_currentPlayer];
}

bool Board::madeChess(Player* player)
{
	int i = 0;
	bool whitePlayer = player->getType() == WHITE_PLAYER;
	// enemy's king identifier
	char kingIdentifier = whitePlayer ? KING : toupper(KING);
	Piece *src = nullptr, *king = nullptr;
	bool didChess = false;
	int moveCode = 0;
	char type = ' ';

	// loop through the board to get the enemey king's piece
	for (i = 0; i < _board.length() && king == nullptr; i++)
	{
		if (_board[i] == kingIdentifier)
		{
			king = getPiece(getLocation(i));
		}
	}

	// loop through the board to check if any of the player's pieces
	// can make a valid move against the enemy king, if yes, its a chess.
	for (i = 0; i < _board.length() && !didChess; i++)
	{
		if ((whitePlayer && isupper(_board[i])) ||
			!whitePlayer && islower(_board[i]))
		{
			// we found one of our player's pieces, lets save it
			src = getPiece(getLocation(i));
			type = src->getType();

			// only check for pieces whom their validateMove function was implemented
			if (type == ROOK || type == PAWN || type == KING || type == BISHOP)
			{
				moveCode = src->basicValidateMove(*player, *king);
				if (moveCode == VALID_MOVE) moveCode = src->validateMove(*king);

				// if all checks passed, its a chess!
				if (moveCode == VALID_MOVE) didChess = true;
			}
		}
	}

	// return final result
	return didChess;
}

bool Board::madeCheckmate(Player* player) {
	int i = 0;
	bool didCheckmate = true;
	bool whitePlayer = player->getType() == WHITE_PLAYER;
	char kingIdentifier = whitePlayer ? KING : toupper(KING);
	Piece *king = nullptr, *dest = nullptr;

	// First, check if the player has made a chess
	if (!madeChess(player)) {
		return false;
	}

	// loop through the board to get the enemey king's piece
	for (i = 0; i < _board.length() && king == nullptr; i++)
	{
		if (_board[i] == kingIdentifier)
		{
			king = getPiece(getLocation(i));
		}
	}

	// save a copy of our board incase of a self-chess
	string boardCopy = _board;

	for (i = 0; i < _board.length() && didCheckmate; i++)
	{
		dest = getPiece(getLocation(i));

		// set current player to enemey, so it can check if enemey's king can move out of chess
		_currentPlayer = (_currentPlayer + 1) % CHESS_PLAYERS;

		// make basic checks, if all basic checks passed, make
		// further checks with the current piece, and send result to graphics
		int result = king->basicValidateMove(getCurrentPlayer(), *dest);
		if (result == VALID_MOVE) result = king->validateMove(*dest);
		if (result == VALID_MOVE)
		{
			_board[king->getIndex()] = '#';

			// move source to desired destination
			_board[dest->getIndex()] = kingIdentifier;

			// restore current player to check for chess
			_currentPlayer = (_currentPlayer + 1) % CHESS_PLAYERS;

			// if madeChess will return false, meaning the king has escaped.
			// and therefore, didCheckmate should be false aswell
			didCheckmate = madeChess(player);

			// restore board
			_board = boardCopy;
		}
		else
		{
			// current player should get restored to its original state
			_currentPlayer = (_currentPlayer + 1) % CHESS_PLAYERS;
		}

		delete dest; // free Piece's memory after use
	}

	// If none of the player's moves allow them to escape the chess,
	// then the player has made a checkmate and the function should
	// return true
	return didCheckmate;
}

int Board::movePiece(Piece& src, Piece& dest)
{
	// save a copy of our board incase of a self-chess
	string boardCopy = _board;
	// empty out source
	_board[src.getIndex()] = '#';

	// move source to desired destination
	_board[dest.getIndex()] = src.getOwner()->getType() == WHITE_PLAYER ? toupper(src.getType()) : src.getType();

	// check if either one of sides did chess
	// and whether they made a self chess or not
	bool whiteDidChess = madeChess(_players[WHITE_PLAYER]);
	bool blackDidChess = madeChess(_players[BLACK_PLAYER]);
	bool whitePlayer = src.getOwner()->getType() == WHITE_PLAYER;

	// if its a self-chess
	if ((whiteDidChess && !whitePlayer) || (blackDidChess && whitePlayer))
	{
		// restore our board and return an invalid move
		_board = boardCopy;
		return INVALID_SELF_CHESS;
	}


	if (madeCheckmate(&getCurrentPlayer()))
	{
		return VALID_CHECKMATE;
	}

	_currentPlayer = (_currentPlayer + 1) % CHESS_PLAYERS;
	// switch turn from black to white and vice versa

	return (whiteDidChess || blackDidChess) ? VALID_CHESS : VALID_MOVE;
}

Piece* Board::getPiece(const string location) const
{
	int index = getIndex(location); //get numeric location
	Piece* piece = nullptr;
	Player* player = isupper(_board[index]) ? _players[WHITE_PLAYER] : _players[BLACK_PLAYER];

	switch (tolower(_board[index]))
	{
	case ROOK:
		piece = new Rook(player, location);
		break;
	case KNIGHT:
		piece = new Knight(player, location);
		break;
	case BISHOP:
		piece = new Bishop(player, location);
		break;
	case KING:
		piece = new King(player, location);
		break;
	case QUEEN:
		piece = new Queen(player, location);
		break;
	case PAWN:
		piece = new Pawn(player, location);
		break;
	default:
		// create an empty piece object to represent an empty spot
		piece = new EmptyPiece(nullptr, location);
		break;
	}

	return piece;
}
