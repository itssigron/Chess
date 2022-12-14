#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop(Player* owner, string location);

	int validateMove(Piece& dest) override;
};