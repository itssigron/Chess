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

void performMove(const string srcLocation, const string destLocation, Board& board, Pipe& p);
void startClient();

int main(int argc, char* argv[])
{
	string filePath = argc > 1 ? argv[1] : "";
	Pipe p;

	// enable virtual terimal processing (ansi color codes)
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	#ifndef _DEBUG
		startClient();
	#endif // !_DEBUG

	srand(time_t(NULL));
	bool isConnect = p.connect();


	// loop until an available pipe has been found
	while (!isConnect)
	{
		cout << "cant connect to graphics... trying to re-connect..." << endl;
		Sleep(500);
		isConnect = p.connect();
	}

	// the first message to the graphics will be our board with 0 at the end to indicate the WHITE_PLAYER is the starting player
	char msgToGraphics[1024] = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR00";
	Board board = Board(string(msgToGraphics), filePath); // initialize our Board class
	string& boardStr = board.getBoard();
	int result = 0;

	std::ifstream file(filePath);
	string history = "";

	// letting graphics know if the game was loaded from a file
	if (filePath.length() && file.is_open())
	{
		msgToGraphics[BOARD_SIZE * BOARD_SIZE + 1] = '1';
		std::getline(file, history); // get file's content (game's history)
	}

	// send the board string
	p.sendMessageToGraphics(msgToGraphics);

	// send history to graphics if game was loaded from file
	if (filePath.length() && file.is_open())
	{
		file.close();
		p.sendMessageToGraphics(history);
	}

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

					// set their movement state to false so they will be able to re-castle
					rook->setMoved(false);
					srcPiece->setMoved(false);

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
			if(move != nullptr) moveRedone = true;
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
		if(msgFromGraphics != "quit") msgFromGraphics = p.getMessageFromGraphics();
	}

	// free program's used memory
	p.close();
	msgFromGraphics.clear();

	return 0;
}
	
void performMove(const string srcLocation, const string destLocation, Board& board, Pipe& p)
{
	// access src and dest pieces using the information from the client
	Move* move = moveRedone ? board.getMovesStack().top() : new Move(srcLocation, destLocation, &board);
	Piece* srcPiece = move->getSrcPiece(true);
	Piece* destPiece = move->getDestPiece(true);
	bool isEmpty = destPiece->getType() == EMPTY_PIECE;
	bool whitePlayer = board.getCurrentPlayer().getType() == WHITE_PLAYER;
	int result = 0;
	string msgFromGraphics;

	// make basic checks, if all basic checks passed, make
	// further checks with the current piece, and send result to graphics
	result = srcPiece->basicValidateMove(board.getCurrentPlayer(), *destPiece);
	if (result == VALID_MOVE)
		result = srcPiece->validateMove(*destPiece);
	int newResult = 0;

	// perform the actual "move"
	if (result == VALID_MOVE || result == VALID_PAWN_PROMOTION || result == VALID_EN_PASSANT || result == VALID_CASTLE)
	{
		// update source piece location + update result incase of "check"/"self-check"
		newResult = board.movePiece(*srcPiece, *destPiece, *move);

		moveRedone = false; // restore state

		if (newResult != INVALID_SELF_CHECK)
		{
			// apply move in graphics
			p.sendMessageToGraphics(srcLocation + destLocation);
		}

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
			}
		}

		if (newResult != VALID_MOVE)
		{
			result = newResult;
		}
	}

	// free pieces's memory after use incase needed
	if (srcPiece->getType() == EMPTY_PIECE)
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

void startClient()
{
	// Get the path and file name of the current executable
	char path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);

	// Convert the char array to a string
	string pathString = path;

	// construct a command to start graphics which is in the same directory as the engine
	string cmd = "cmd /c start \"\" \"" + pathString.substr(0, pathString.find_last_of('\\')) + "\\ChessClient.exe\"";

	//start the client and hide engine's console window
	system(cmd.c_str());
	::ShowWindow(::GetConsoleWindow(), SW_HIDE); // hide console window so only game client visible
}