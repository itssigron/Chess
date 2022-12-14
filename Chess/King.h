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

	int validateMove(Piece& dest) override;
};

