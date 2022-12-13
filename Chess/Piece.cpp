#include "Piece.h"

string Piece::getLocation(int index)
{
	string result = "";
	char dictionary[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	int row = index / 8;
	int col = index % 8;

	result = dictionary[col];
	result += (8 - row) + '0'; // we start from top which is row 8

	return result;
}

Piece::Piece(Player* owner, string location, char type)
{
	_owner = owner;
	_location = location;
	_type = type;
	_killed = false;
}

Player* Piece::getOwner()
{
	return _owner;
}

string Piece::getLocation()
{
	return _location;
}

char Piece::getType()
{
	return _type;
}

void Piece::setLocation(string location)
{
	_location = location;
}

void Piece::setType(char type)
{
	_type = type;
}

int Piece::basicValidateMove(Player& currentPlayer, Piece& dest)
{
	int result = VALID_MOVE; // assume move is valid until proven wrong

	if (_type == EMPTY_PIECE)
	{
		result = INVALID_SRC_MISSING_PIECE; //src location doesnt have a piece on it
	}
	else if (currentPlayer.getType() != _owner->getType())
	{
		result = INVALID_PIECE_MOVE; // its not his turn.
	}
	else if (this->_location == dest._location)
	{
		result = INVALID_SAME_LOCATION; // src and dest on the same location
	}
	else if (dest._type != EMPTY_PIECE && _owner->getType() == dest._owner->getType())
	{
		result = INVALID_DEST_PLAYER; // current player cant kill his own piece
	}

	std::cout << "A move from " << _location << " to " << dest._location
		<< " resulted in code " << result << std::endl;

	//finished all basic checks, return final result
	return result;
}

std::ostream& operator<<(std::ostream& os, const Piece& obj)
{
	return std::cout << (char)(obj._owner && obj._owner->getType() == WHITE_PLAYER ? toupper(obj._type) : obj._type);
}
