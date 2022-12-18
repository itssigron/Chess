#include "Knight.h"

Knight::Knight(Player* owner, string location) : Piece(owner, location, KNIGHT)
{

}

int Knight::validateMove(Piece& dest)
{
	// src row and col
	int x1 = _location[0] - 'a', y1 = _location[1] - '0';
	// dest row and col
	int x2 = dest.getLocation()[0] - 'a', y2 = dest.getLocation()[1] - '0';

	if ((abs(x2 - x1) == 1 && abs(y2 - y1) == 2) || (abs(x2 - x1) == 2 && abs(y2 - y1) == 1))
	{
		return VALID_MOVE;
	}

	return INVALID_PIECE_MOVE;
}
