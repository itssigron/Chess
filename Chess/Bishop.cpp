#include "Bishop.h"

Bishop::Bishop(Player* owner, string location) : Piece(owner, location, BISHOP)
{

}

int Bishop::move(Piece& dest)
{
	return VALID_MOVE;
}
