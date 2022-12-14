#pragma once
#include "Piece.h"
class King : public Piece
{
public:
	King(Player* owner, string location);

	int validateMove(Piece& dest) override;
};

