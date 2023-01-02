#include "Rook.h"

Rook::Rook(Player* owner, string location) : Piece(owner, location, ROOK)
{

}

int Rook::validateMove(Piece& dest)
{
	int srcRow = getRank(), destRow = dest.getRank();
	int srcCol = getFile() - 'a', destCol = dest.getFile() - 'a';

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
			_owner->getBoard().getBoard()[Board::getIndex(Board::getLocation((char)(col + 'a'), row))] != EMPTY_PIECE;

		// go on to the next square in the rook's path
		row += rowOffset;
		col += colOffset;
	}

	return foundPiece ? INVALID_PIECE_MOVE : VALID_MOVE;
}