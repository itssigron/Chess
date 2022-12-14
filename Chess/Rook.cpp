#include "Rook.h"

Rook::Rook(Player* owner, string location) : Piece(owner, location, ROOK)
{

}

// todo: optimize this function
int Rook::validateMove(Piece& dest)
{
	char srcRow = _location[1], srcCol = _location[0];
	char destRow = dest.getLocation()[1], destCol = dest.getLocation()[0];
	bool foundPiece = false; // loop flag to whether we found a non-empty piece in the rook's path
	char i = 0;
	int bigger = 0, lower = 0;

	if (srcRow == destRow) // horizontally
	{
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

		if (foundPiece)
		{
			return INVALID_PIECE_MOVE;
		}
	}
	else if (srcCol == destCol) // vertically
	{
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

		if (foundPiece)
		{
			return INVALID_PIECE_MOVE;
		}
	}
	else
	{
		// if he neither moves horizontally nor vertically, its an invalid move
		return INVALID_PIECE_MOVE;
	}

	// if all checks passed, its a valid move
	return VALID_MOVE;
}
