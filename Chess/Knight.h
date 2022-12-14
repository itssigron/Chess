#pragma once
#include "Piece.h"
class Knight : public Piece
{
public:
	Knight(Player* owner, string location);

	int validateMove(Piece& dest) override;
};

