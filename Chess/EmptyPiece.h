#pragma once
#include "Piece.h"
class EmptyPiece : public Piece
{
public:
	EmptyPiece(Player* owner, string location);

	int validateMove(Piece& dest) override;
};


