#pragma once
#include "Board.h"
#include <vector>

#define WHITE_PLAYER 0
#define BLACK_PLAYER 1

// protect against circular reference
class Board;
class Piece;

class Player
{
private:
	int _type; // either WHITE_PLAYER or BLACK_PLAYER
	std::vector<Piece*> _pieces; // all player's pieces:
	Board* _board; // the board in which this player belongs to
	
public:
	/*
	* Initiates our Player object
	* input: The pointer to the board where this player belongs to, and the player's types
	* output: the Player object
	*/
	Player(Board* board, int type);

	/*
	* Clears all used memory in the player's constructor
	* input: none
	* output: none
	*/
	~Player();

	/*
	* Gets the player type
	* input: none
	* output: the player's type (WHITE_PLAYER or BLACK_PLAYER)
	*/
	const int& getType() const;

	/*
	* Gets the player's pieces
	* input: none
	* output: the player's pieces vector
	*/
	std::vector<Piece*>& getPieces();

	/*
	* Gets the board
	* input: none
	* output: the board which this player belongs in
	*/
	Board& getBoard();
};

