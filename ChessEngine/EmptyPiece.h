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

	int validateMove(Piece& dest) override;
};


