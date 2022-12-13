#pragma once

#define WHITE_PLAYER 0
#define BLACK_PLAYER 1


class Player
{
private:
	int _type;
public:
	Player();
	Player(int type);
	int getType() const;
};

