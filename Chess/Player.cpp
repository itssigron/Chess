#include "Player.h"

Player::Player(Board* board, int type)
{
	if (type != WHITE_PLAYER && type != BLACK_PLAYER)
	{
		//todo: throw an error
	}
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