#include "King.h"

King::King(Player* owner, string location) : Piece(owner, location, KING)
{

}

int King::move(Piece& dest)
{
	return VALID_MOVE;
}
