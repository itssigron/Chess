#pragma once
#include "Board.h"

#define WHITE_PLAYER 0
#define BLACK_PLAYER 1

// protect against circular reference
class Board;

class Player
{
private:
	int _type; // either WHITE_PLAYER or BLACK_PLAYER
	Board* _board; // 
public:
	/*
	* Initiates our Player object
	* input: The pointer to the board where this player belongs to, and the player's types
	* output: the Player object
	*/
	Player(Board* board, int type);

	/*
	* Gets the player type
	* input: none
	* output: the player's type (WHITE_PLAYER or BLACK_PLAYER)
	*/
	const int& getType() const;

	/*
	* Gets the board
	* input: none
	* output: the board which this player belongs in
	*/
	Board& getBoard();
};

