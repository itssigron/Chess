#include "Rook.h"

Rook::Rook(Player* owner, string location) : Piece(owner, location, ROOK)
{

}

int Rook::move(Piece& dest)
{
	return VALID_MOVE;
}
