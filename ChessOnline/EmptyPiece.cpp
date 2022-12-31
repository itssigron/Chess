#include "EmptyPiece.h"

EmptyPiece::EmptyPiece(Player* owner, string location) : Piece(owner, location, EMPTY_PIECE) {}

int EmptyPiece::validateMove(Piece& dest)
{
	return INVALID_SRC_MISSING_PIECE;
}