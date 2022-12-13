#pragma once
#include "Piece.h"
class Knight : public Piece
{
public:
	Knight(Player* owner, string location);

	int move(Piece& dest) override;
};

