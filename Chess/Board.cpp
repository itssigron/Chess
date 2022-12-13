#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"
#include "EmptyPiece.h"


Board::Board()
{
	_board = nullptr;
	_currentPlayer = WHITE_PLAYER;
	_gameFinished = false;
	_players[0] = Player(WHITE_PLAYER);
	_players[1] = Player(BLACK_PLAYER);
}

Board::Board(const string& board)
{
	_players[WHITE_PLAYER] = Player(WHITE_PLAYER);
	_players[BLACK_PLAYER] = Player(BLACK_PLAYER);
	_currentPlayer = board[64] - '0';
	_gameFinished = false;

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

const Player* Board::getPlayers() const
{
	return _players;
}

Player& Board::getCurrentPlayer()
{
	return _players[_currentPlayer];
}

bool Board::isGameFinished() const
{
	return _gameFinished;
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
			location = Piece::getLocation(index);
			// rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR
			player = isupper(board[index]) ? &_players[WHITE_PLAYER] : &_players[BLACK_PLAYER];

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

Player* Board::getWinner()
{
	return _gameFinished ? &_players[_currentPlayer] : nullptr;
}

Piece& Board::getPiece(string location) const
{
	int i = 0, j = 0;
	Piece* result = nullptr;

	for (i = 0; i < 8 && !result; i++)
	{
		for (j = 0; j < 8 && !result; j++)
		{
			if (_board[i][j]->getLocation() == location)
			{
				result = _board[i][j];
			}
		}
	}

	return *result;
}
