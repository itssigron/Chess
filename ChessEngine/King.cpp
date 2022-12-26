#include "King.h"
#pragma warning (disable : 6001)

King::King(Player* owner, string location) : Piece(owner, location, KING)
{

}

int King::validateMove(Piece& dest)
{
	Piece* rook = nullptr;
	Piece *firstSquare = nullptr, *secondSquare = nullptr, *thirdSquare = nullptr;
	bool firstSquareEmpty = false, secondSquareEmpty = false, thirdSquareEmpty = false;

	Board& board = _owner->getBoard();

	// src row and col
	int x1 = getFile() - 'a', y1 = getRank();
	// dest row and col
	int x2 = dest.getFile() - 'a', y2 = dest.getRank();
	int isValid = INVALID_PIECE_MOVE;

	// Calculate offset for row and col (whether we move left or right)
	int colOffset = (x1 < x2) ? 1 : -1;
	int firstSquareCol = x1 + colOffset;
	int secondSquareCol = firstSquareCol + colOffset;
	int thirdSquareCol = secondSquareCol + colOffset;

	int usedCastleRow = 0;
	int usedCastleCol = 0;

	// a king can move 1 square to any direction,
	// so as long the difference between src col, dest col and src row, dest row isnt above 1, its a valid move
	if ((abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1))
	{
		isValid = VALID_MOVE;
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
			// Now we need to check if: 1. both squares are empty and 2. both squares arent under attack
			firstSquare = board.getPiece(board.getLocation(usedCastleRow, firstSquareCol));
			secondSquare = board.getPiece(board.getLocation(usedCastleRow, secondSquareCol));
			thirdSquare = board.getPiece(board.getLocation(usedCastleRow, thirdSquareCol));
			firstSquareEmpty = firstSquare->getType() == EMPTY_PIECE;
			secondSquareEmpty = secondSquare->getType() == EMPTY_PIECE;
			thirdSquareEmpty = thirdSquare->getType() == EMPTY_PIECE;

			if (firstSquareEmpty && secondSquareEmpty && (usedCastleCol == QUEENSIDE_ROOK_COL ? thirdSquareEmpty : true))
			{
				isValid = VALID_CASTLE;
				
				if (board.moveWillCauseCheck(*this, *firstSquare))
				{
					isValid = INVALID_PIECE_MOVE;
				}

				// free memory after use
				if (firstSquareEmpty)
				{
					delete firstSquare;
				}
				if (secondSquareEmpty)
				{
					delete secondSquare;
				}
				if (thirdSquareEmpty)
				{
					delete thirdSquare;
				}
			}
		}
	}
	return isValid;
}