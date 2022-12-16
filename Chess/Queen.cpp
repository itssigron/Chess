#include "Queen.h"

Queen::Queen(Player* owner, string location) : Piece(owner, location, QUEEN)
{

}

int Queen::validateMove(Piece& dest)
{
	Bishop b = Bishop(this->_owner, this->_location);
	Rook r = Rook(this->_owner, this->_location);

	// check if either of the moves is correct (assuming VALID_MOVE is 0)
	return b.validateMove(dest) & r.validateMove(dest);
}
