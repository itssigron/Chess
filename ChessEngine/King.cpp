#include "King.h"

King::King(Player* owner, string location) : Piece(owner, location, KING)
{

}

int King::validateMove(Piece& dest)
{
	Piece* rook1;
	Piece* rook2;
	
	// src row and col
	int x1 = _location[0] - 'a', y1 = _location[1] - '0';
	// dest row and col
	int x2 = dest.getLocation()[0] - 'a', y2 = dest.getLocation()[1] - '0';
	int isValid = INVALID_PIECE_MOVE;

	// Calculate offset for row and col (whether we move horizontally left/right or vertically up/down)
	int rowOffset = (x1 < x2) ? 1 : ((x1 > x2) ? -1 : 0);
	int row = x1 + rowOffset;

	bool foundPiece = false;
	int usedCastleRow = 0;
	
	// check if king wants and can castle
	if (y1 == y2 && _hasntMoved && (x1 == POSSIBLE_CASTLE_COL1 || x2 == POSSIBLE_CASTLE_COL2))
	{
		// Check player color
		if (_owner->getType() == WHITE_PLAYER)
			usedCastleRow = POSSIBLE_CASTLE_ROW1;

		else if (_owner->getType() == BLACK_PLAYER)
			usedCastleRow = POSSIBLE_CASTLE_ROW2;

		rook1 = _owner->_board->getPiece(_owner->_board->getLocation(usedCastleRow, ROOK1_COL));
		rook2 = _owner->_board->getPiece(_owner->_board->getLocation(usedCastleRow, ROOK2_COL));
		
		// Check if rooks on the back rank are found and haven't moved yet
		if ((rook1->getType() == ROOK && rook1->_hasntMoved) || (rook2->getType() == ROOK && rook2->_hasntMoved))
		{
			// Check no pieces are on the way
			/* DOESNT WORK
			while ((row != x2) && !foundPiece) 
			{
				// if theres a piece in the king's path, update flag accordingly
				foundPiece = _owner->getBoard().getBoard()[Board::getIndex(string(1, usedCastleRow + 'a') + (char)(row + '0'))] != EMPTY_PIECE;

				// go on to the next square in the king's path
				row += rowOffset;
			}*/
			foundPiece = 0; // assume no pieces 

			// Piece was not found which means castle is possible
			if (!foundPiece)
			{
				// Check which rook to move
				if (x2 == POSSIBLE_CASTLE_COL1)
					//_owner->_board->movePiece(*rook1, *_owner->_board->getPiece(_owner->_board->getLocation(usedCastleRow, ROOK1_COL + 2)), ?));

				if (x2 == POSSIBLE_CASTLE_COL2)
					//_owner->_board->movePiece(*rook1, *_owner->_board->getPiece(_owner->_board->getLocation(usedCastleRow, ROOK2_COL - 4)), ?));
				
				isValid = VALID_MOVE;
			}

		}
		if (rook1->getType() == EMPTY_PIECE)
			delete rook1;
		if (rook2->getType() == EMPTY_PIECE)
			delete rook2;
	}
	// a king can move 1 square to any direction,
	// so as long the difference between src col, dest col and src row, dest row isnt above 1, its a valid move
	else if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1)
		isValid = VALID_MOVE;

	if (isValid == VALID_MOVE && !_hasntMoved) // If piece makes first valid move, make sure it marks it in the variable
		_hasntMoved = 0;
	

	return isValid;
}
