#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"
#include "EmptyPiece.h"


string Board::getLocation(int& index)
{
	int row = index / BOARD_SIZE;
	int col = index % BOARD_SIZE;

	// BOARD_SIZE - row because we start from top
	return string(1, col + 'a') + (char)((BOARD_SIZE - row) + '0');
}

int Board::getIndex(string& location)
{
	// row * BOARD_SIZE + col
	return (BOARD_SIZE - (location[1] - '0')) * BOARD_SIZE + (location[0] - 'a');
}

Board::Board()
{
	_board = nullptr;
	_currentPlayer = WHITE_PLAYER;
	_players[WHITE_PLAYER] = nullptr;
	_players[BLACK_PLAYER] = nullptr;
}

Board::Board(const string& board)
{
	_players[WHITE_PLAYER] = new Player(this, WHITE_PLAYER);
	_players[BLACK_PLAYER] = new Player(this, BLACK_PLAYER);
	// last char is which player is starting
	_currentPlayer = board[BOARD_SIZE * BOARD_SIZE] - '0';

	initBoard(); // allocate memory for board
	setBoard(board); //fill its places with pieces
}

Board::~Board()
{
	int i = 0, j = 0;

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			delete _board[i][j];
		}
	}
}

Piece*** Board::getBoard() const
{
	return _board;
}

Player** Board::getPlayers()
{
	return _players;
}

Player& Board::getCurrentPlayer()
{
	return *_players[_currentPlayer];
}

void Board::setBoard(const string& board)
{
	int i = 0, j = 0;
	int index = 0;
	Piece* piece = nullptr;
	Player* player = nullptr;
	string location = "";

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			index = i * 8 + j;
			location = Board::getLocation(index); //get stringifed location
			// rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR
			player = isupper(board[index]) ? _players[WHITE_PLAYER] : _players[BLACK_PLAYER];

			switch (tolower(board[index]))
			{
			case ROOK:
				_board[i][j] = new Rook(player, location);
				break;
			case KNIGHT:
				_board[i][j] = new Knight(player, location);
				break;
			case BISHOP:
				_board[i][j] = new Bishop(player, location);
				break;
			case KING:
				_board[i][j] = new King(player, location);
				break;
			case QUEEN:
				_board[i][j] = new Queen(player, location);
				break;
			case PAWN:
				_board[i][j] = new Pawn(player, location);
				break;
			default:
				_board[i][j] = new EmptyPiece(nullptr, location);
				break;
			}
		}
	}
}

void Board::initBoard()
{
	int i = 0, j = 0;
	_board = new Piece * *[8];

	for (i = 0; i < 8; i++)
	{
		_board[i] = new Piece * [8];
		for (j = 0; j < 8; j++)
		{
			_board[i][j] = nullptr;
		}
	}
}

void Board::setPiece(Piece& src, Piece& dest)
{
	int i = 0, j = 0;
	int srcRow = 0, srcCol = 0;
	int destRow = 0, destCol = 0;

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (_board[i][j]->getLocation() == src.getLocation())
			{
				srcRow = i;
				srcCol = j;
			}
			if (_board[i][j]->getLocation() == dest.getLocation())
			{
				destRow = i;
				destCol = j;
			}
		}
	}

	// empty out source
	_board[srcRow][srcCol] = new EmptyPiece(nullptr, src.getLocation());

	src.setLocation(dest.getLocation()); //update location
	delete _board[destRow][destCol]; // free spot
	_board[destRow][destCol] = &src; // transfer source to dest

	// switch turn from black to white and vice versa
	_currentPlayer = (_currentPlayer + 1) % 2;
}

Piece& Board::getPiece(string location) const
{
	int index = Board::getIndex(location); //get numeric location
	int row = index / 8, col = index % 8;
	return *_board[row][col];
}
