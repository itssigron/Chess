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
	* Validate knight's move
	* Input: Destination knight wants to go to
	* Output: Valid or not
	*/
	int validateMove(Piece& dest) override;
};

