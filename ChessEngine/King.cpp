#include "King.h"
#pragma warning (disable : 6001)

King::King(Player* owner, string location) : Piece(owner, location, KING)
{

}

int King::validateMove(Piece& dest)
{
	Piece* rook = nullptr;
	Piece* firstSquare = nullptr;
	Piece* secondSquare = nullptr;
	bool firstSquareEmpty = false;
	bool secondSquareEmpty = false;

	bool whitePlayer = _owner->getType() == WHITE_PLAYER;
	Board& board = _owner->getBoard();
	string& boardStr = board.getBoard();
	Player* enemy = whitePlayer ? board.getPlayers()[BLACK_PLAYER] : board.getPlayers()[WHITE_PLAYER];
	string boardCopy;
	boardCopy.assign(boardStr);

	string oldLocation = getLocation();

	// src row and col
	int x1 = _location[0] - 'a', y1 = _location[1] - '0';
	// dest row and col
	int x2 = dest.getLocation()[0] - 'a', y2 = dest.getLocation()[1] - '0';
	int isValid = INVALID_PIECE_MOVE;

	// Calculate offset for row and col (whether we move left or right)
	int colOffset = (x1 < x2) ? 1 : -1;
	int firstSquareCol = x1 + colOffset;
	int secondSquareCol = firstSquareCol + colOffset;

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
		usedCastleRow = whitePlayer ? POSSIBLE_WHITE_CASTLE_ROW : POSSIBLE_BLACK_CASTLE_ROW;
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
			firstSquareEmpty = firstSquare->getType() == EMPTY_PIECE;
			secondSquareEmpty = secondSquare->getType() == EMPTY_PIECE;

			if (firstSquareEmpty && secondSquareEmpty)
			{
				isValid = VALID_CASTLE;

				//todo: check if both pieces arent under attack by any of the enemy's pieces
				board.shiftCurrentPlayer();
				// make basic checks, if all basic checks passed, make
				// further checks with the current piece
				int result = basicValidateMove(*_owner, *firstSquare);
				if (result == VALID_MOVE)
				{
					result = validateMove(*firstSquare);
				}
				if (result == VALID_MOVE)
				{
					// empty out source
					boardStr[getIndex()] = '#';

					// move source to desired destination
					boardStr[firstSquare->getIndex()] = getIdentifier();

					setLocation(firstSquare->getLocation()); // update piece location

					bool enemyDidChess = board.madeChess(enemy);
					if (enemyDidChess)
					{
						isValid = INVALID_PIECE_MOVE;
					}

					// restore our board state
					boardStr = boardCopy;
					setLocation(oldLocation);
				}

				board.shiftCurrentPlayer();

				// free memory after use
				if (firstSquareEmpty)
				{
					delete firstSquare;
				}
				if (secondSquareEmpty)
				{
					delete secondSquare;
				}
			}
		}
	}
	return isValid;
}