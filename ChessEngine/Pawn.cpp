#include "Pawn.h"
#include <math.h>
#include "globalVars.h"

Pawn::Pawn(Player* owner, string location) : Piece(owner, location, PAWN)
{

}

int Pawn::validateMove(Piece& dest)
{
	int srcRow = getRank(), destRow = dest.getRank();
	char srcCol = getFile(), destCol = dest.getFile();
	int whiteDiff = destRow - srcRow, blackDiff = srcRow - destRow;
	bool whitePlayer = _owner->getType() == WHITE_PLAYER;
	bool emptyPiece = dest.getType() == EMPTY_PIECE;
	int result = INVALID_PIECE_MOVE;
	std::stack<Move*> movesHistory = _owner->getBoard().getMovesStack();
	Move* lastMove = movesHistory.empty() ? nullptr : movesHistory.top();
	Move* secondLastMove = nullptr;
	bool possibleEnPassant = false;

	if (lastMove != nullptr && (moveRedone && movesHistory.size() >= 2 || !moveRedone))
	{
		if (moveRedone)
		{
			movesHistory.pop();
			secondLastMove = movesHistory.top();
			movesHistory.push(lastMove); // restore stack
			lastMove = secondLastMove;
		}
		int lastSrcRow = lastMove->getSrc()[1] - '0', lastDestRow = lastMove->getDest()[1] - '0';
		char lastSrcCol = lastMove->getSrc()[0], lastDestCol = lastMove->getDest()[0];

		// if the last move was a valid pawn initial 2 squares move 
		// and the current move is from the same place (1 col diff) from the initial enemy pawn move ,then it could possibly be "en passant"
		possibleEnPassant = (lastSrcCol == lastDestCol) && (srcRow == lastDestRow) && abs(srcCol - lastDestCol) == 1 &&
			(abs(lastSrcRow - lastDestRow) == 2) && (lastSrcRow == WHITE_PAWNS_INDEX || lastSrcRow == BLACK_PAWNS_INDEX);
	}


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
	// 4. en passant (last moves moved 2 squares forward [initial pawn move]),
	// and this move the pawn moves diagonally to "en passant capture" this pawn
	
	if (abs(srcCol - destCol) == 1 && emptyPiece && possibleEnPassant && 
		((whitePlayer && whiteDiff == 1) || (!whitePlayer && blackDiff == 1)))
	{
		int rowOffset = whitePlayer ? -1 : 1;
		Piece* capturedPiece = _owner->getBoard().getPiece(Board::getLocation(destCol, destRow + rowOffset));
		if (capturedPiece->getType() == EMPTY_PIECE)
		{
			delete capturedPiece; // empty piece - invalid move + delete its memory since its an empty piece
		}
		else
		{
			result = VALID_EN_PASSANT;
		}
	}
	else if (srcCol == destCol || (!emptyPiece && abs(srcCol - destCol) == 1))
	{
		// make sure user cannot "kill" a piece 1 square forward
		if (!(srcCol == destCol && !emptyPiece))
		{
			if (whitePlayer && (whiteDiff == 1 || (srcCol == destCol && whiteDiff == 2 && srcRow == WHITE_PAWNS_INDEX)))
			{
				result = VALID_MOVE;
			}
			else if (!whitePlayer && (blackDiff == 1 || (srcCol == destCol && blackDiff == 2 && srcRow == BLACK_PAWNS_INDEX)))
			{
				result = VALID_MOVE;
			}

			// if its the initial move of the pawn and he wants to move 2 squares forward,
			// make sure there isnt a piece on the pawn's way
			if (result == VALID_MOVE && (blackDiff == 2 || whiteDiff == 2))
			{
				int rowOffset = whitePlayer ? 1 : -1;
				Piece* middlePiece = _owner->getBoard().getPiece(Board::getLocation(srcCol, srcRow + rowOffset));
				if (middlePiece->getType() != EMPTY_PIECE)
				{
					result = INVALID_PIECE_MOVE;
				}
				else
				{
					delete middlePiece;
				}
			}
		}
	}

	
	// if a pawn reaches his farthest rank, he can promote his pawn
	if (result == VALID_MOVE && ((destRow == WHITE_FARTHEST_RANK && whitePlayer ) || (destRow == BLACK_FARTHEST_RANK && !whitePlayer)))
	{
		result = VALID_PAWN_PROMOTION;
	}
	// return final result code
	return result;
}
