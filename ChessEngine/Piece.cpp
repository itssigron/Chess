#include "Piece.h"

const char Piece::getIdentifier(const char& pieceType, const int side)
{
	return side == WHITE_PLAYER ? toupper(pieceType) : pieceType;
}

Piece::Piece(Player* owner, const string location, const char type)
{
	_owner = owner;
	_location = location;
	_type = type;
	_movedAt = nullptr;
	_identifier = owner == nullptr ? EMPTY_PIECE : owner->getType() == WHITE_PLAYER ? toupper(type) : type;
}

Piece::~Piece()
{
	_location.clear();
}

const Player* Piece::getOwner() const
{
	return _owner;
}

const string& Piece::getLocation() const
{
	return _location;
}

const int Piece::getIndex() const
{
	return Board::getIndex(getLocation());
}

const char& Piece::getType() const
{
	return _type;
}

const bool& Piece::isCaptured() const
{
	return _captured;
}

const Move* Piece::movedAt() const
{
	return _movedAt;
}

const char& Piece::getIdentifier() const
{
	return _identifier;
}

void Piece::setLocation(const string& location)
{
	_location = location;
}

void Piece::setType(const char type)
{
	_type = type;
}

void Piece::setCaptured(const bool isCaptured)
{
	_captured = isCaptured;
}

void Piece::setMovedAt(Move* move)
{
	_movedAt = move;
}

const char Piece::getFile() const
{
	return _location[0];
}

const int Piece::getRank() const
{
	return _location[1] - '0';
}

int Piece::basicValidateMove(const Player* currentPlayer, Piece& dest)
{
	int result = VALID_MOVE; // assume move is valid until proven wrong

	if (_type == EMPTY_PIECE || currentPlayer->getType() != _owner->getType())
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