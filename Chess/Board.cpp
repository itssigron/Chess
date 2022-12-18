#pragma warning(disable : 6011)

#include "EmptyPiece.h"
#include <windows.h> // WinApi header
#include "Board.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

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

string Board::getAllPossibleMoves(Piece& src)
{
	Piece* dest;
	int i = 0, j = 0;
	string locations = "";
	string boardCopy = _board;
	string oldLocation = src.getLocation();
	Player* enemy = _players[WHITE_PLAYER] == src.getOwner() ? _players[BLACK_PLAYER] : _players[WHITE_PLAYER];

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			dest = getPiece(getLocation(i, j));

			// make basic checks, if all basic checks passed, make
			// further checks with the current piece
			int result = src.basicValidateMove(getCurrentPlayer(), *dest);
			if (result == VALID_MOVE)
			{
				result = src.validateMove(*dest);
			}
			if (result == VALID_MOVE || result == VALID_PAWN_PROMOTION)
			{
				// empty out source
				_board[src.getIndex()] = '#';

				// move source to desired destination
				_board[dest->getIndex()] = src.getIdentifier();

				src.setLocation(dest->getLocation()); // update piece location

				// if a capture was made, then perform the action on the player's pieces
				if (dest->getType() != EMPTY_PIECE)
				{
					dest->setCaptured(true);
				}

				bool enemyDidChess = madeChess(enemy);

				// restore our board state
				_board = boardCopy;
				src.setLocation(oldLocation);
				dest->setCaptured(false);

				// if its not a self-chess
				if (!enemyDidChess)
				{
					// push valid move's location
					locations += dest->getLocation();
				}
			}

			if (dest->getType() == EMPTY_PIECE)
			{
				delete dest; // free Piece's memory after use
			}
		}
	}

	return locations;
}

void Board::printAllValidLocations(Piece& src)
{
	Piece* dest;
	int i = 0, j = 0;
	string validMovesLocations = getAllPossibleMoves(src);

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
				if (validMovesLocations.find(dest->getLocation()) != string::npos)
				{
					// all valid moves should be printed in green (or blue if its a capture move)
					std::cout << (dest->getType() == EMPTY_PIECE ? "\033[0;32m" : "\033[0;34m") << *dest << "\033[0m";
				}
				else
				{
					std::cout << *dest;
				}
			}
			if (dest->getType() == EMPTY_PIECE)
			{
				delete dest; // free Piece's memory after use
			}
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
	// last char is which player is starting
	_currentPlayer = board[BOARD_SIZE * BOARD_SIZE] - '0';
	_board = board;
	_board.pop_back(); // remove the starting player char

	// initiate our 2 players's objects
	_players[WHITE_PLAYER] = new Player(this, WHITE_PLAYER);
	_players[BLACK_PLAYER] = new Player(this, BLACK_PLAYER);
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
	Player* enemy = _players[whitePlayer ? BLACK_PLAYER : WHITE_PLAYER];
	// enemy's king identifier
	char kingIdentifier = whitePlayer ? KING : toupper(KING);
	Piece* src = nullptr, * king = nullptr;
	bool didChess = false;
	int moveCode = 0;
	char type = ' ';
	std::vector<Piece*> pieces = player->getPieces();
	std::vector<Piece*> enemyPieces = enemy->getPieces();

	// loop through the board to get the enemey king's piece
	for (i = 0; i < enemyPieces.size() && king == nullptr; i++)
	{
		if (enemyPieces[i]->getIdentifier() == kingIdentifier)
		{
			king = enemyPieces[i];
		}
	}

	// loop through the board to check if any of the player's pieces
	// can make a valid move against the enemy king, if yes, its a chess.
	for (i = 0; i < pieces.size() && !didChess; i++)
	{
		// we found one of our player's pieces, lets save it
		src = pieces[i];
		if (!src->isCaptured())
		{
			type = src->getType();

			moveCode = src->basicValidateMove(*player, *king);
			if (moveCode == VALID_MOVE)
			{
				moveCode = src->validateMove(*king);
			}

			// if all checks passed, its a chess!
			if (moveCode == VALID_MOVE || moveCode == VALID_PAWN_PROMOTION)
			{
				didChess = true;
			}
		}
	}

	// return final result
	return didChess;
}

bool Board::madeCheckmate(Player* player)
{
	int i = 0, j = 0;
	bool didCheckmate = true;
	bool whitePlayer = player->getType() == WHITE_PLAYER;
	Player* enemy = _players[whitePlayer ? BLACK_PLAYER : WHITE_PLAYER];
	Piece* src = nullptr, * dest = nullptr;
	std::vector<Piece*> pieces = player->getPieces();
	std::vector<Piece*> enemyPieces = enemy->getPieces();

	// First, check if the player has made a chess
	if (!madeChess(player))
	{
		return false;
	}

	// loop through the board to get the enemey king's piece
	for (i = 0; i < enemyPieces.size() && didCheckmate; i++)
	{
		src = enemyPieces[i];
		if (!src->isCaptured())
		{

			// save a copy of our board incase of a self-chess
			string boardCopy = _board;
			string location = src->getLocation();

			for (j = 0; j < _board.length() && didCheckmate; j++)
			{
				dest = getPiece(getLocation(j));

				// set current player to enemey, so it can check if enemey's king can move out of chess
				_currentPlayer = (_currentPlayer + 1) % CHESS_PLAYERS;

				// make basic checks, if all basic checks passed, make
				//// further checks with the current piece, and send result to graphics
				int result = src->basicValidateMove(getCurrentPlayer(), *dest);
				if (result == VALID_MOVE)
					result = src->validateMove(*dest);
				if (result == VALID_MOVE || result == VALID_PAWN_PROMOTION)
				{
					_board[src->getIndex()] = '#';

					// move source to desired destination
					_board[dest->getIndex()] = src->getIdentifier();
					src->setLocation(dest->getLocation());

					// restore current player to check for chess
					_currentPlayer = (_currentPlayer + 1) % CHESS_PLAYERS;

					// if madeChess will return false, meaning the king has escaped.
					// and therefore, didCheckmate should be false aswell
					didCheckmate = madeChess(player);

					// restore board
					_board = boardCopy;
					src->setLocation(location);
				}
				else
				{
					// current player should get restored to its original state
					_currentPlayer = (_currentPlayer + 1) % CHESS_PLAYERS;
				}

				if (dest->getType() == EMPTY_PIECE)
				{
					delete dest; // free Piece's memory after use
				}
			}
		}
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
	string oldLocation = src.getLocation();
	// empty out source
	_board[src.getIndex()] = '#';

	// move source to desired destination
	_board[dest.getIndex()] = src.getIdentifier();

	src.setLocation(dest.getLocation()); // update piece location

	// if a capture was made, then perform the action on the player's pieces
	if (dest.getType() != EMPTY_PIECE)
	{
		dest.setCaptured(true);
	}

	// check if either one of sides did chess
	// and whether they made a self chess or not
	bool whiteDidChess = madeChess(_players[WHITE_PLAYER]);
	bool blackDidChess = madeChess(_players[BLACK_PLAYER]);
	bool whitePlayer = src.getOwner()->getType() == WHITE_PLAYER;

	// if its a self-chess
	if ((whiteDidChess && !whitePlayer) || (blackDidChess && whitePlayer))
	{
		// restore our board state and return an invalid move
		_board = boardCopy;
		src.setLocation(oldLocation);
		dest.setCaptured(false);
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

int Board::promotePiece(Piece* promoted, char newType)
{
	// since this function is called after the move has been complete, we should "switch" the turn to get the previous player
	// which was promoted
	_currentPlayer = (_currentPlayer + 1) % CHESS_PLAYERS;
	Player* player = &getCurrentPlayer();
	std::vector<Piece*>& pieces = player->getPieces();
	string location = promoted->getLocation();
	Piece* newPiece = nullptr;
	int i = 0;
	bool foundPiece = false;
	int result = 0;

	for (i = 0; i < pieces.size() && !foundPiece; i++)
	{
		foundPiece = pieces[i]->getLocation() == location;
	}

	i--; // to get the index of pieces in which "promoted" is in

	switch (newType)
	{
	case QUEEN:
		newPiece = new Queen(player, location);
		break;
	case ROOK:
		newPiece = new Rook(player, location);
		break;
	case BISHOP:
		newPiece = new Bishop(player, location);
		break;
	case KNIGHT:
		newPiece = new Knight(player, location);
		break;
	default:
		// a default "promotion"
		newPiece = new Pawn(player, location);
	}

	delete promoted;										  // we dont need this piece anymore
	pieces[i] = newPiece;									  // assign our new promoted piece to the pieces vector
	_board[newPiece->getIndex()] = newPiece->getIdentifier(); // update the board

	// check if promotion caused check/checkmate
	if (madeCheckmate(&getCurrentPlayer()))
	{
		result = VALID_CHECKMATE;
	}
	else if (madeChess(player))
	{
		result = VALID_CHESS;
	}
	else
	{
		result = SUCCESSFUL_PROMOTION;
	}

	// reset current player's state
	_currentPlayer = (_currentPlayer + 1) % CHESS_PLAYERS;

	return result;
}

Piece* Board::getPiece(const string location) const
{
	int i = 0;
	int index = getIndex(location); // get numeric location
	Piece* piece = nullptr;
	Player* player = isupper(_board[index]) ? _players[WHITE_PLAYER] : _players[BLACK_PLAYER];
	std::vector<Piece*> pieces = player->getPieces();

	if (_board[index] == EMPTY_PIECE)
	{
		// create an empty piece object
		piece = new EmptyPiece(nullptr, location);
	}
	else
	{
		for (i = 0; i < pieces.size(); i++)
		{
			if (pieces[i]->getLocation() == location && !pieces[i]->isCaptured())
			{
				piece = pieces[i];
			}
		}
	}

	return piece;
}
