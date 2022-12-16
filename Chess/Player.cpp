#include "Player.h"

Player::Player(Board* board, int type)
{
	_type = type;
	_board = board;
}

const int& Player::getType() const
{
	return _type;
}

Board& Player::getBoard()
{
	return *_board;
}