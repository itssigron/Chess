#pragma once
#include "Piece.h"
class King : public Piece
{
public:
	King(Player* owner, string location);

	int move(Piece& dest) override;
};

