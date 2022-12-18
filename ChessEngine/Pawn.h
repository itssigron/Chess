#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	/*
	* Initiates the Pawn - defines the owner, location and sets Piece type to PAWN
	* input: owner and stringifed location
	* output: the Pawn
	*/
	Pawn(Player* owner, string location);

	int validateMove(Piece& dest) override;
};


