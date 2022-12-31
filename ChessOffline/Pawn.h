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

	/*
	* Validates the pawn's move - 2 squares forward on initial move, 1 square forward normal move
	* 1 diagonal square if move makes capture / en passant
	* input: destination piece
	* output: result move code
	*/
	int validateMove(Piece& dest) override;
};


