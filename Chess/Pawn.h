#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	Pawn(Player* owner, string location);

	int move(Piece& dest) override;
};


