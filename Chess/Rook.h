#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	Rook(Player* owner, string location);

	int move(Piece& dest) override;
};

