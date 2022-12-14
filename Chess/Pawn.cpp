#include "Pawn.h"

Pawn::Pawn(Player* owner, string location) : Piece(owner, location, PAWN)
{

}

int Pawn::validateMove(Piece& dest)
{
	return VALID_MOVE;
}
