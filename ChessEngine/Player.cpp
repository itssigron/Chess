#include "Player.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"

int Player::timesCalled = 0;

Player::Player(Board* board, int type)
{
	int i = 0;
	int start = 0, end = 0;
	Piece* piece = nullptr;
	const string& boardStr = board->getBoard();
	string location = "";

	_type = type;
	_board = board;

	// go through all player's pieces
	for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		location = Board::getLocation(i);

		// only if the piece belongs to the current player
		if (Piece::getIdentifier(tolower(boardStr[i]), type) == boardStr[i])
		{
			switch (tolower(boardStr[i]))
			{
			case ROOK:
				piece = new Rook(this, location);
				break;
			case KNIGHT:
				piece = new Knight(this, location);
				break;
			case BISHOP:
				piece = new Bishop(this, location);
				break;
			case KING:
				piece = new King(this, location);
				break;
			case QUEEN:
				piece = new Queen(this, location);
				break;
			case PAWN:
				piece = new Pawn(this, location);
				break;
			default:
				break;
			}
		}
		// push the created piece into our pieces vector
		if(piece) _pieces.push_back(piece);
		piece = nullptr;
	}
}

Player::~Player()
{
	int i = 0;
	for (i = 0; i < _pieces.size(); i++)
	{
		delete _pieces[i]; //clear piece memory
	}
	_pieces.clear();
}

const int& Player::getType() const
{
	timesCalled++;
	return _type;
}

const std::vector<Piece*>& Player::getPieces() const
{
	return _pieces;
}


Board& Player::getBoard()
{
	return *_board;
}

Piece* Player::getKing() const
{
	int i = 0;
	Piece* king = nullptr;

	for (i = 0; i < _pieces.size() && king == nullptr; i++)
	{
		if (_pieces[i]->getType() == KING)
		{
			king = _pieces[i];
		}
	}

	return king;
}
