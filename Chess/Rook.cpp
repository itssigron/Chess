#include "Rook.h"

Rook::Rook(Player* owner, string location) : Piece(owner, location, ROOK)
{

}

// todo: optimize this function
int Rook::validateMove(Piece& dest)
{
	// check for both horizontally and vertically
	// as its the only possible moves for a rook
	int result = validateHorizontally(dest);
	return result == VALID_MOVE ? VALID_MOVE : validateVertically(dest);
}
