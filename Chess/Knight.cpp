#include "Knight.h"

Knight::Knight(Player* owner, string location) : Piece(owner, location, KNIGHT)
{

}

int Knight::validateMove(Piece& dest)
{
	return VALID_MOVE;
}
