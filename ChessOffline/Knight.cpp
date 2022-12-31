#include "Knight.h"

Knight::Knight(Player* owner, string location) : Piece(owner, location, KNIGHT) {}

int Knight::validateMove(Piece& dest)
{
	// src file and rank
	int x1 = getFile(), y1 = getRank();
	// dest file and rank
	int x2 = dest.getFile(), y2 = dest.getRank();

	if ((abs(x2 - x1) == 1 && abs(y2 - y1) == 2) || (abs(x2 - x1) == 2 && abs(y2 - y1) == 1))
	{
		return VALID_MOVE;
	}

	return INVALID_PIECE_MOVE;
}
