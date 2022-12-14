#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:
	Queen(Player* owner, string location);

	int validateMove(Piece& dest) override;
};

