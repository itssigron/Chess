#include "EmptyPiece.h"

EmptyPiece::EmptyPiece(Player* owner, string location) : Piece(owner, location, EMPTY_PIECE)
{

}

int EmptyPiece::move(Piece& dest)
{
	return VALID_MOVE;
}