#include "King.h"

King::King(Player* owner, string location) : Piece(owner, location, KING)
{

}

int King::validateMove(Piece& dest)
{
	// src row and col
	int x1 = _location[0] - 'a', y1 = _location[1] - '0';
	// dest row and col
	int x2 = dest.getLocation()[0] - 'a', y2 = dest.getLocation()[1] - '0';

	if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1)
	{
		return VALID_MOVE;
	}
	return INVALID_PIECE_MOVE;
}
