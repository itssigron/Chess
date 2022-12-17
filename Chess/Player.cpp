#include "Player.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"

Player::Player(Board* board, int type)
{
	int i = 0;
	int start = 0, end = 0;
	Piece* piece = nullptr;
	const string& boardStr = board->getBoard();
	string location = "";

	_type = type;
	_board = board;

	start = type == BLACK_PLAYER ? 0 : BOARD_SIZE * (BOARD_SIZE - EACH_PLAYER_ROWS); // black starts at the top and white starts at the bottom
	end = start + (BOARD_SIZE * EACH_PLAYER_ROWS); // simply add the amount of pieces each side has to the start to get its end


	// go through all player's pieces
	for (i = start; i < end; i++)
	{
		location = Board::getLocation(i);
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

		// push the created piece into our pieces vector
		_pieces.push_back(piece);
	}
}

const int& Player::getType() const
{
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