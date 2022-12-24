#include "King.h"
#pragma warning (disable : 6001)

King::King(Player* owner, string location) : Piece(owner, location, KING)
{

}

int King::validateMove(Piece& dest)
{
	Piece* rook;

	Board& board = _owner->getBoard();
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
	int usedCastleCol = 0;

	// a king can move 1 square to any direction,
	// so as long the difference between src col, dest col and src row, dest row isnt above 1, its a valid move
	if ((abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1))
	{

	}
	// check if king wants and can castle
	else if (y1 == y2 && !_hasMoved && (x2 == POSSIBLE_QUEENSIDE_CASTLE_COL || x2 == POSSIBLE_KINGSIDE_CASTLE_COL))
	{
		// Check player color
		usedCastleRow = _owner->getType() == WHITE_PLAYER ? POSSIBLE_WHITE_CASTLE_ROW : POSSIBLE_BLACK_CASTLE_ROW;
		usedCastleCol = x2 == POSSIBLE_QUEENSIDE_CASTLE_COL ? QUEENSIDE_ROOK_COL : KINGSIDE_ROOK_COL;

		rook = board.getPiece(board.getLocation(usedCastleRow, usedCastleCol));
		char pieceType = rook->getType();

		if (pieceType != ROOK)
		{
			if (pieceType == EMPTY_PIECE)
			{
				delete rook;
			}
			return INVALID_PIECE_MOVE;
		}

		// Check if rook hasnt moved yet
		if (!rook->hasMoved())
		{
			isValid = VALID_CASTLE;
			// Check no pieces are on the way
			/* DOESNT WORK
			while ((row != x2) && !foundPiece)
			{
				// if theres a piece in the king's path, update flag accordingly
				foundPiece = _owner->getBoard().getBoard()[Board::getIndex(string(1, usedCastleRow + 'a') + (char)(row + '0'))] != EMPTY_PIECE;

				// go on to the next square in the king's path
				row += rowOffset;
			}
			foundPiece = 0; // assume no pieces 
			
			// Piece was not found which means castle is possible
			if (!foundPiece)
			{
				// Check which rook to move
				if (x2 == POSSIBLE_KINGSIDE_CASTLE_COL)
					//_owner->_board->movePiece(*rook1, *_owner->_board->getPiece(_owner->_board->getLocation(usedCastleRow, ROOK1_COL + 2)), ?));

					if (x2 == POSSIBLE_QUEENSIDE_CASTLE_COL)
						//_owner->_board->movePiece(*rook1, *_owner->_board->getPiece(_owner->_board->getLocation(usedCastleRow, ROOK2_COL - 4)), ?));

						isValid = VALID_MOVE;
			}*/
		}
	}

	return isValid;
}
