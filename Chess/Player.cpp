#include "Player.h"

Player::Player()
{
	_type = WHITE_PLAYER;
}

Player::Player(int type)
{
	if (type != WHITE_PLAYER && type != BLACK_PLAYER)
	{
		//todo: throw an error
	}
	_type = type;
}

int Player::getType() const
{
	return _type;
}
