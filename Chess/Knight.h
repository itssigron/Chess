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

	int validateMove(Piece& dest) override;
};

