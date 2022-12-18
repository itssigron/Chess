#include "Pawn.h"
#include <math.h>

Pawn::Pawn(Player* owner, string location) : Piece(owner, location, PAWN)
{

}

int Pawn::validateMove(Piece& dest)
{
	int srcRow = _location[1] - '0', destRow = dest.getLocation()[1] - '0';
	char srcCol = _location[0], destCol = dest.getLocation()[0];
	int whiteDiff = destRow - srcRow, blackDiff = srcRow - destRow;
	bool whitePlayer = _owner->getType() == WHITE_PLAYER, blackPlayer = _owner->getType() == BLACK_PLAYER;
	bool emptyPiece = dest.getType() == EMPTY_PIECE;
	int result = INVALID_PIECE_MOVE;


	// check if either one of the following:
	// 1. moved 1 square forward to a FREE spot (dest is empty)
	// white can move 1 square from bottom to top
	// black can move 1 square from top to bottom
	// 
	// 2. moved 2 square forward to a FREE spot (dest is empty)
	// white can move 2 squares from bottom to top if its his first move
	// black can move 2 squares from top to bottom if its his first move
	// 
	// 3. made a diagonal move by 1 square ONLY if dest spot is taken by a Piece
	// white can make diagonal move either to the top-left or top-right
	// black can make diagonal move either to the bottom-right or bottom-left
	if (srcCol == destCol || (!emptyPiece && abs(srcCol - destCol) == 1))
	{
		// make sure user cannot "kill" a piece 1 square forward
		if (!(srcCol == destCol && !emptyPiece))
		{
			if (whitePlayer && (whiteDiff == 1 || whiteDiff == 2 && srcRow == WHITE_PAWNS_INDEX))
			{
				result = VALID_MOVE;
			}
			else if (blackPlayer && (blackDiff == 1 || blackDiff == 2 && srcRow == BLACK_PAWNS_INDEX))
			{
				result = VALID_MOVE;
			}
		}
	}

	
	// if a pawn reaches his farthest rank, he can promote his pawn
	if (result == VALID_MOVE && (destRow == 8 && whitePlayer || destRow == 1 && !whitePlayer))
	{
		result = VALID_PAWN_PROMOTION;
	}
	// return final result code
	return result;
}
