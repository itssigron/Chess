#pragma once
#include "Piece.h"
class King : public Piece
{
public:
	/*
	* Initiates the King - defines the owner, location and sets Piece type to KING
	* input: owner and stringifed location
	* output: the King
	*/
	King(Player* owner, string location);

	/*
	* Validates the king's move - 1 square on any direction,
	* and possibly 2 squares to left/right if he wants to castle
	* input: destination piece
	* output: result move code
	*/
	int validateMove(Piece& dest) override;
};

