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
					// all valid moves should be printed in green
					std::cout << "\033[0;32m" << *dest << "\033[0m";
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

void Board::movePiece(Piece& src, Piece& dest)
{
	// empty out source
	_board[src.getIndex()] = '#';

	// move source to desired destination
	_board[dest.getIndex()] = src.getOwner()->getType() == WHITE_PLAYER ? toupper(src.getType()) : src.getType();

	// switch turn from black to white and vice versa
	_currentPlayer = (_currentPlayer + 1) % CHESS_PLAYERS;
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
