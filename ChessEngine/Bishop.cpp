#include "Bishop.h"

Bishop::Bishop(Player* owner, string location) : Piece(owner, location, BISHOP)
{

}

int Bishop::validateMove(Piece& dest)
{
	int srcRow = _location[1] - '0', destRow = dest.getLocation()[1] - '0';
	int srcCol = _location[0] - 'a', destCol = dest.getLocation()[0] - 'a';
	int squaresMovedY = abs(destRow - srcRow), squaresMovedX = abs(destCol - srcCol);

	// Calculate offset for row and col (whether we move diagonally top-left/top-right/bottom-left/bottom-right)
	int rowOffset = (srcRow < destRow) ? 1 : -1, colOffset = (srcCol < destCol) ? 1 : -1;
	int row = srcRow + rowOffset, col = srcCol + colOffset;

	bool foundPiece = false;

	// if the squares the bishop moved from x and y arent equal it means its not a diagonal move
	if (squaresMovedX != squaresMovedY)
	{
		return INVALID_PIECE_MOVE;
	}

	// moves diagonally until a piece is found, if we found a piece then its an invalid move
	while (row != destRow + rowOffset && col != destCol && !foundPiece) {
		// if theres a piece in the bishop's path, update flag accordingly
		foundPiece =
			_owner->getBoard().getBoard()[Board::getIndex(string(1, col + 'a') + (char)(row + '0'))] != EMPTY_PIECE;

		// go on to the next diagonal square
		row += rowOffset;
		col += colOffset;
	}

	return foundPiece ? INVALID_PIECE_MOVE : VALID_MOVE;
}
