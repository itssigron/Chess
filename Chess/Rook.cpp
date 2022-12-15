#include "Rook.h"

Rook::Rook(Player* owner, string location) : Piece(owner, location, ROOK)
{

}

// todo: optimize this function
int Rook::validateMove(Piece& dest)
{
	// src row and col
	int x1 = _location[0] - 'a', y1 = _location[1] - '0';
	// dest row and col
	int x2 = dest.getLocation()[0] - 'a', y2 = dest.getLocation()[1] - '0';

	int biggerX = x1 > x2 ? x1 : x2, smallerX = x1 < x2 ? x1 : x2;
	int biggerY = y1 > y2 ? y1 : y2, smallerY = y1 < y2 ? y1 : y2;
	int smaller = x1 == x2 ? smallerY : smallerX, bigger = x1 == x2 ? biggerY : biggerX;
	
	int i = 0;
	int row = 0, col = 0;
	bool foundPiece = false; // loop flag
	string& board = _owner->getBoard().getBoard();

	// if its neither horizontally nor vertically, return invalid move
	if (x1 != x2 && y1 != y2)
	{
		return INVALID_PIECE_MOVE;
	}

	// in the loop, smaller gets added with 1 because theres no need to check 
	// for both src and dest pieces since they were already validated.

	// validate both vertically and horizontally
	for (i = smaller + 1; i < bigger && !foundPiece; i++)
	{
		// get row and col based on loop index, x and y's
		x1 == x2 ? (row = BOARD_SIZE - i, col = x1) : (row = BOARD_SIZE - y1, col = i);

		// if pieace isnt empty, set it to true and return invalid move
		foundPiece = board[Board::getIndex(row, col)] != EMPTY_PIECE;
	}
	
	// if a piece wasnt found in the middle of the rook's path, return valid move
	return foundPiece ? INVALID_PIECE_MOVE : VALID_MOVE;
}
