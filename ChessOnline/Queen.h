#pragma once
#include "Piece.h"
#include "Bishop.h"
#include "Rook.h"
class Queen : public Piece
{
public:
	/*
	* Initiates the Queen - defines the owner, location and sets Piece type to QUEEN
	* input: owner and stringifed location
	* output: the Queen
	*/
	Queen(Player* owner, string location);

	/*
	* Validates the queen's move - as many squares as he want to any direction
	* basically just a combination of both a rook and a knight
	* input: destination piece
	* output: result move code
	*/
	int validateMove(Piece& dest) override;
};

