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

	/*
	* Validate bishop move
	* Input: destination bishop wants to go to
	* Output: Valid or not
	*/
	int validateMove(Piece& dest) override;
};