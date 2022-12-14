#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	Rook(Player* owner, string location);

	/*
	* A function to validate the rook's move, it makes sure he can only move horizontally and vertically
	* + it makes sure there isnt a piece in its path
	* input: the destination piece
	* output: the result move code
	*/
	int validateMove(Piece& dest) override;
};

