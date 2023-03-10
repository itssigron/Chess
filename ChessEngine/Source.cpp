/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include <fstream>
#include "Board.h"
#include "Queen.h"
#include "Move.h"
#include "Pawn.h"
#include "globalVars.h"

using std::cout;
using std::endl;
using std::string;
bool moveRedone = false;

/*
* performs the move in-board + in-graphics, handle move errors and in perfect communication with graphics
* input: source piece location, dest piece location, board and pipe
* output: none
*/
void performMove(const string srcLocation, const string destLocation, Board& board, Pipe& p);

int main()
{
	Pipe p;

	ShowWindow(::GetConsoleWindow(), SW_HIDE);

	srand(time_t(NULL));
	bool isConnect = p.connect();


	// loop until an available pipe has been found
	while (!isConnect)
	{
		cout << "cant connect to graphics... trying to re-connect..." << endl;
		isConnect = p.connect();
	}

	// the first message to the graphics will be our board with 0 at the end to indicate the WHITE_PLAYER is the starting player
	char msgToGraphics[1024] = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR00";
	Board board = Board(string(msgToGraphics)); // initialize our Board class
	string& boardStr = board.getBoard();
	int result = 0;

	// send the board string
	p.sendMessageToGraphics(msgToGraphics);

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit" && msgFromGraphics != "") // an empty string can be considered as a "quit"
	{
		if (msgFromGraphics == "history") // graphics wants to get history
		{
			p.sendMessageToGraphics(board.getMoveHistory());
		}
		else if (msgFromGraphics == "undo")
		{
			Move* move = board.undoMove();
			if (move != nullptr)
			{
				char identifier = move->getCaptured() == nullptr ? EMPTY_PIECE : move->getCaptured()->getIdentifier();
				char isEnPassant = move->isEnPassant() + '0'; // '0' for false and '1' for true
				char isCastling = move->isCastling() + '0';
				char isPromoted = move->isPromoted() + '0';
				Piece* srcPiece = move->getSrcPiece(true);

				// if its the piece's first move, set its movedAt state to nullptr
				if (srcPiece->movedAt() == move)
				{
					srcPiece->setMovedAt(nullptr);
				}

				// format is {dest}{src}{captured identifier if any} will undo move in graphics
				p.sendMessageToGraphics(move->getDest() + move->getSrc() + identifier + isEnPassant + isCastling + isPromoted);

				if (move->isCastling())
				{
					string srcLocation = move->getSrc(), destLocation = move->getDest();
					char srcCol = srcLocation[0], destCol = destLocation[0];
					int colOffset = srcCol - destCol > 0 ? 1 : -1;
					char rookCol = destCol + colOffset;
					string rookLocation = Board::getLocation(rookCol, destLocation[1]);
					string rookOriginalLocation = Board::getLocation(colOffset == 1 ? 'a' : 'h', destLocation[1]);
					Piece* rook = board.getPiece(rookLocation);

					// update rook to its original location before the castle
					boardStr[Board::getIndex(rookOriginalLocation)] = rook->getIdentifier();
					boardStr[Board::getIndex(rookLocation)] = EMPTY_PIECE;
					rook->setLocation(rookOriginalLocation);

					// restore rook's location in graphics
					p.sendMessageToGraphics(rookLocation + rookOriginalLocation);
				}

				if (move->isPromoted())
				{
					board.promotePiece(srcPiece, PAWN); // demote back to pawn
				}

				move->setCaptured(nullptr); // un-capture if move resulted in capture
			}
			else
			{
				p.sendMessageToGraphics("");
			}
		}
		else if (msgFromGraphics == "redo")
		{
			Move* move = board.redoMove();
			char isEnPassant = move == nullptr ? ' ' : move->isEnPassant() + '0'; // '0' for false and '1' for true
			p.sendMessageToGraphics(move == nullptr ? "" : (move->getSrc() + move->getDest() + isEnPassant));
			if (move != nullptr) moveRedone = true;
		}
		// source piece selection, meaning we want to send all of its possible moves to graphics
		else if (msgFromGraphics.length() == 2)
		{
			Piece* srcPiece = board.getPiece(msgFromGraphics);
			p.sendMessageToGraphics(board.getAllPossibleMoves(*srcPiece));


			// free piece's memory after use incase needed
			if (srcPiece->getType() == EMPTY_PIECE)
			{
				delete srcPiece;
			}
		}
		else // graphics sent command to make the move
		{
			// perform the move and let graphics know the result
			performMove(msgFromGraphics.substr(0, 2), msgFromGraphics.substr(2, 4), board, p);
		}

		// get message from graphics
		if (msgFromGraphics != "quit") msgFromGraphics = p.getMessageFromGraphics();
	}

	// free program's used memory
	p.close();
	msgFromGraphics.clear();

	return 0;
}

void performMove(const string srcLocation, const string destLocation, Board& board, Pipe& p)
{
	// we use moveRedone as a "cache", if this move is a result of a redo, 
	// then we already pushed the move onto the stack,
	// so we can just get it instead of creating new Move object
	Move* move = moveRedone ? board.getMovesStack().top() : new Move(srcLocation, destLocation, &board);
	Piece* srcPiece = move->getSrcPiece(true);
	Piece* destPiece = move->getDestPiece(true);
	bool isEmpty = destPiece->getType() == EMPTY_PIECE;
	bool whitePlayer = board.getCurrentPlayer()->getType() == WHITE_PLAYER;
	int result = 0;
	int newResult = 0;
	string msgFromGraphics = "";

	// validate move
	result = board.validateMove(board.getCurrentPlayer(), *srcPiece, *destPiece);

	// perform the actual "move"
	if (board.isValidMove(result))
	{
		// update source piece location + update result incase of "check"/"self-check"
		newResult = board.movePiece(*srcPiece, *destPiece, *move);

		moveRedone = false; // restore state

		if (newResult != INVALID_SELF_CHECK)
		{
			// apply move in graphics
			p.sendMessageToGraphics(srcLocation + destLocation);
		}

		// if the new result is not an endgame result, then continue to check for special moves
		if (newResult == VALID_MOVE || newResult == VALID_CHECK)
		{
			if (result == VALID_EN_PASSANT)
			{
				char destCol = destPiece->getFile();
				int rowOffset = whitePlayer ? -1 : 1;
				string capturedPieceLocation = destPiece->getLocation();
				capturedPieceLocation[1] += rowOffset;
				Piece* capturedPiece = board.getPiece(capturedPieceLocation);
				capturedPiece->setCaptured(true);
				move->setCaptured(capturedPiece);
				move->setEnPassant(true);
				board.getBoard()[Board::getIndex(capturedPieceLocation)] = EMPTY_PIECE;

				// capture piece in graphics
				p.sendMessageToGraphics(capturedPieceLocation);
			}
			else if (result == VALID_CASTLE)
			{
				char row = move->getDest()[1];
				int srcCol = (move->getDest()[0] - 'a') == POSSIBLE_KINGSIDE_CASTLE_COL ? KINGSIDE_ROOK_COL : QUEENSIDE_ROOK_COL;
				int destCol = srcCol == KINGSIDE_ROOK_COL ? AFTER_KINGSIDE_CASTLE_ROOK : AFTER_QUEENSIDE_CASTLE_ROOK;
				string rookSrcLocation = Board::getLocation((char)(srcCol + 'a'), row);
				string rookDestLocation = Board::getLocation((char)(destCol + 'a'), row);;
				Piece* rook = board.getPiece(rookSrcLocation);
				board.getBoard()[rook->getIndex()] = EMPTY_PIECE;
				board.getBoard()[Board::getIndex(rookDestLocation)] = rook->getIdentifier();
				rook->setLocation(rookDestLocation);
				move->setCastling(true);

				// apply rook's move in graphics
				p.sendMessageToGraphics(rookSrcLocation + rookDestLocation);
			}
			else if (result == VALID_PAWN_PROMOTION)
			{
				// promote the piece to whatever the user chose in graphics
				p.sendMessageToGraphics(std::to_string(result));

				msgFromGraphics = p.getMessageFromGraphics();
				result = board.promotePiece(board.getPiece(msgFromGraphics.substr(0, 2)), msgFromGraphics[2]);
				move->setPromoted(true);
				srcPiece = nullptr;
			}
		}

		if (newResult != VALID_MOVE)
		{
			result = newResult;
		}
	}

	// free pieces's memory after use incase needed

	// here we check for nullptr because if pawn is being promoted,
	// then srcPiece will get deleted and set to nullptr
	if (srcPiece != nullptr && srcPiece->getType() == EMPTY_PIECE)
	{
		delete srcPiece;
	}
	if (destPiece->getType() == EMPTY_PIECE)
	{
		delete destPiece;
	}

	// send the result code to graphics
	// constants for the codes can be found in Piece.h
	p.sendMessageToGraphics(std::to_string(result));

	// game over, send end-game history to graphics
	if (newResult == VALID_CHECKMATE || newResult == VALID_STALEMATE || newResult == VALID_INSUFFICIENT_MATERIAL)
	{
		msgFromGraphics = p.getMessageFromGraphics(); // get the quit message
		p.sendMessageToGraphics(board.getMoveHistory());
	}

	// finish current move
	p.sendMessageToGraphics("done");
}