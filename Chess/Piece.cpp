#include "Piece.h"

Piece::Piece(Player* owner, string location, char type)
{
	_owner = owner;
	_location = location;
	_type = type;
}

Piece::~Piece()
{
	_location.clear();
}

const Player* Piece::getOwner() const
{
	return _owner;
}

string& Piece::getLocation()
{
	return _location;
}

int Piece::getIndex()
{
	return Board::getIndex(getLocation());
}

const char& Piece::getType() const
{
	return _type;
}

void Piece::setLocation(string& location)
{
	_location = location;
}

void Piece::setType(char& type)
{
	_type = type;
}

int Piece::basicValidateMove(Player& currentPlayer, Piece& dest)
{
	int result = VALID_MOVE; // assume move is valid until proven wrong

	if (_type == EMPTY_PIECE || currentPlayer.getType() != _owner->getType())
	{
		//src location doesnt have the current player's piece on it
		result = INVALID_SRC_MISSING_PIECE;
	}
	else if (this->_location == dest._location)
	{
		result = INVALID_SAME_LOCATION; // src and dest on the same location
	}
	else if (dest._type != EMPTY_PIECE && _owner->getType() == dest._owner->getType())
	{
		result = INVALID_DEST_PLAYER; // current player cant kill his own piece
	}

	//finished all basic checks, return final result
	return result;
}

std::ostream& operator<<(std::ostream& os, const Piece& obj)
{
	return std::cout << (char)(obj._owner && obj._owner->getType() == WHITE_PLAYER ? toupper(obj._type) : obj._type);
}
