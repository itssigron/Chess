#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	/*
	* Initiates the Bishop - defines the owner, location and sets Piece type to BISHOP
	* input: owner and stringifed location
	* output: the Bishop
	*/
	Bishop(Player* owner, string location);

	int validateMove(Piece& dest) override;
};