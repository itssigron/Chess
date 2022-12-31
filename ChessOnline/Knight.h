#pragma once
#include "Piece.h"
class Knight : public Piece
{
public:
	/*
	* Initiates the Knight - defines the owner, location and sets Piece type to KNIGHT
	* input: owner and stringifed location
	* output: the Knight
	*/
	Knight(Player* owner, string location);

	/*
	* Validates the knights's move - as many squares as he wants + diagonal direction only,
	* input: destination piece
	* output: result move code
	*/
	int validateMove(Piece& dest) override;
};

