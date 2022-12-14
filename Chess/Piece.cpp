#include "Piece.h"

Piece::Piece(Player* owner, string location, char type)
{
	_owner = owner;
	_location = location;
	_type = type;
}

const Player* Piece::getOwner() const
{
	return _owner;
}

string& Piece::getLocation()
{
	return _location;
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

	std::cout << "A move from " << _location << " to " << dest._location
		<< " resulted in code " << result << std::endl;

	//finished all basic checks, return final result
	return result;
}

int Piece::validateVertically(Piece& dest)
{
	char srcRow = _location[1], srcCol = _location[0];
	char destRow = dest.getLocation()[1], destCol = dest.getLocation()[0];
	bool foundPiece = false; // loop flag to whether we found a non-empty piece in the rook's path
	char i = 0;
	int bigger = 0, lower = 0;

	 // if its not vertically, return invalid move
	if (srcCol != destCol) return INVALID_PIECE_MOVE;

	bigger = srcRow > destRow ? srcRow : destRow;
	lower = bigger == srcRow ? destRow : srcRow;
	// loop through all pieces in the path (excluding src and dest pieces)
	// we dont need to check for src and dest because it was already validated
	for (i = lower + 1; i < bigger && !foundPiece; i++)
	{
		// if there is a piece in the rook's path, move is invalid.
		if (_owner->getBoard().getPiece(string(1, srcCol) + i).getType() != EMPTY_PIECE)
		{
			foundPiece = true;
		}
	}

	return foundPiece ? INVALID_PIECE_MOVE : VALID_MOVE;
}

int Piece::validateHorizontally(Piece& dest)
{
	char srcRow = _location[1], srcCol = _location[0];
	char destRow = dest.getLocation()[1], destCol = dest.getLocation()[0];
	bool foundPiece = false; // loop flag to whether we found a non-empty piece in the rook's path
	char i = 0;
	int bigger = 0, lower = 0;

	// if its not horizontally, return invalid move
	if (srcRow != destRow) return INVALID_PIECE_MOVE;

	bigger = srcCol > destCol ? srcCol : destCol;
	lower = bigger == srcCol ? destCol : srcCol;
	// loop through all pieces in the path (excluding src and dest pieces)
	// we dont need to check for src and dest because it was already validated
	for (i = lower + 1; i < bigger && !foundPiece; i++)
	{
		// if there is a piece in the rook's path, move is invalid.
		if (_owner->getBoard().getPiece(string(1, i) + srcRow).getType() != EMPTY_PIECE)
		{
			foundPiece = true;
		}
	}

	return foundPiece ? INVALID_PIECE_MOVE : VALID_MOVE;
}

std::ostream& operator<<(std::ostream& os, const Piece& obj)
{
	return std::cout << (char)(obj._owner && obj._owner->getType() == WHITE_PLAYER ? toupper(obj._type) : obj._type);
}
