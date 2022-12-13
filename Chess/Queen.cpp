#include "Queen.h"

Queen::Queen(Player* owner, string location) : Piece(owner, location, QUEEN)
{

}

int Queen::move(Piece& dest)
{
	return VALID_MOVE;
}
