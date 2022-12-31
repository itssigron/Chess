#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	/*
	* Initiates the Rook - defines the owner, location and sets Piece type to ROOK
	* input: owner and stringifed location
	* output: the Rook
	*/
	Rook(Player* owner, string location);

	/*
	* Validates the rook's move - as many square as he want to either horizontal or vertical direction,
	* input: destination piece
	* output: result move code
	*/
	int validateMove(Piece& dest) override;
};

