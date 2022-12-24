#include "Rook.h"

Rook::Rook(Player* owner, string location) : Piece(owner, location, ROOK)
{

}

int Rook::validateMove(Piece& dest)
{
	int srcRow = _location[1] - '0', destRow = dest.getLocation()[1] - '0';
	int srcCol = _location[0] - 'a', destCol = dest.getLocation()[0] - 'a';

	// Rooks can only move horizontally or vertically, so if the row or column doesn't change
	// then the move is invalid
	if (srcRow != destRow && srcCol != destCol)
	{
		return INVALID_PIECE_MOVE;
	}

	// Calculate offset for row and col (whether we move horizontally left/right or vertically up/down)
	int rowOffset = (srcRow < destRow) ? 1 : ((srcRow > destRow) ? -1 : 0);
	int colOffset = (srcCol < destCol) ? 1 : ((srcCol > destCol) ? -1 : 0);
	int row = srcRow + rowOffset, col = srcCol + colOffset;

	bool foundPiece = false;

	// moves horizontally or vertically until a piece is found, if we found a piece then its an invalid move
	while ((row != destRow || col != destCol) && !foundPiece) {
		// if theres a piece in the rook's path, update flag accordingly
		foundPiece =
			_owner->getBoard().getBoard()[Board::getIndex(string(1, col + 'a') + (char)(row + '0'))] != EMPTY_PIECE;

		// go on to the next square in the rook's path
		row += rowOffset;
		col += colOffset;
	}

	if (foundPiece && !_hasntMoved) // If piece makes first valid move, make sure it marks it in the variable 
		_hasntMoved = 0;

	return foundPiece ? INVALID_PIECE_MOVE : VALID_MOVE;
}