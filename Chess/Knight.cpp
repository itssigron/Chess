#include "Knight.h"

Knight::Knight(Player* owner, string location) : Piece(owner, location, KNIGHT)
{

}

int Knight::move(Piece& dest)
{
	return VALID_MOVE;
}
