#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:
	/*
	* Initiates the Queen - defines the owner, location and sets Piece type to QUEEN
	* input: owner and stringifed location
	* output: the Queen
	*/
	Queen(Player* owner, string location);

	int validateMove(Piece& dest) override;
};

