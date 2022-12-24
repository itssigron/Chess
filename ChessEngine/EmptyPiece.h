#pragma once
#include "Piece.h"
class EmptyPiece : public Piece
{
public:
	/*
	* Initiates the EmptyPiece - defines the owner, location and sets Piece type to EMPTY_PIECE
	* input: owner and stringifed location
	* output: the EmptyPiece
	*/
	EmptyPiece(Player* owner, string location);

	/*
		Validate move
		Input: Destination piece wants to go to
		Output: Valid
	*/
	int validateMove(Piece& dest) override;
};


