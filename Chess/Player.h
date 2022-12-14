#pragma once
#include "Board.h"

#define WHITE_PLAYER 0
#define BLACK_PLAYER 1

class Board;

class Player
{
private:
	int _type;
	Board* _board;
public:
	Player();
	Player(Board* board, int type);
	int getType() const;
	Board& getBoard();
};

