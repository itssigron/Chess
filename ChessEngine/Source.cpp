/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Board.h"
#include "Queen.h"
#include "Move.h"

using std::cout;
using std::endl;
using std::string;

int main()
{
	Pipe p;

	// enable virtual terimal processing (ansi color codes)
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	#ifndef _DEBUG
		//start the client
		system("start ChessClient.exe");
		::ShowWindow(::GetConsoleWindow(), SW_HIDE); // hide console window so only game client visible
		Sleep(1000); // wait for client to start
	#endif // !_DEBUG


	srand(time_t(NULL));
	bool isConnect = p.connect();

	// if connection failed, ask the user if he wants to re-connect or not,
	// until theres either a successful reconnection or the user chose not to.
	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics... trying to re-connect..." << endl;
		Sleep(1000);
		isConnect = p.connect();
	}
	
	ans.clear();

	// the first message to the graphics will be our board with 0 at the end to indicate the WHITE_PLAYER is the starting player
	char msgToGraphics[1024] = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0";
	Board board = Board(string(msgToGraphics)); // initialize our Board class
	int result = 0;

	p.sendMessageToGraphics(msgToGraphics); // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit" && msgFromGraphics != "") // an empty string can be considered as a "quit"
	{
		if (msgFromGraphics == "history") // graphics wants to get history, give it over
		{
			strcpy_s(msgToGraphics, board.getMoveHistory().c_str());
		}
		else if (msgFromGraphics == "undo")
		{
			Move* move = board.undoMove();
			char identifier = move == nullptr ? ' ' :
				move->getCaptured() == nullptr ? EMPTY_PIECE : move->getCaptured()->getIdentifier();
			char isEnPassant = move == nullptr ? ' ' : move->isEnPassant() + '0'; // '0' for false and '1' for true

			// format is {dest}{src}{captured identifier if any} will undo move in graphics
			strcpy_s(msgToGraphics, move == nullptr ? "" : (move->getDest() + move->getSrc() + identifier + isEnPassant).c_str());
			if (move != nullptr && move->getCaptured() != nullptr)
			{
				move->setCaptured(nullptr); // un-capture
			}
		}
		else if (msgFromGraphics == "redo")
		{
			Move* move = board.redoMove();
			char isEnPassant = move == nullptr ? ' ' : move->isEnPassant() + '0'; // '0' for false and '1' for true
			strcpy_s(msgToGraphics, move == nullptr ? "" : (move->getSrc() + move->getDest() + isEnPassant).c_str());
		}
		// source piece selection, meaning we want to send all of its possible moves to graphics
		else if (msgFromGraphics.length() == 2)
		{
			Piece* srcPiece = board.getPiece(msgFromGraphics);
			strcpy_s(msgToGraphics, board.getAllPossibleMoves(*srcPiece).c_str());

			// free piece's memory after use incase needed
			if (srcPiece->getType() == EMPTY_PIECE)
			{
				delete srcPiece;
			}
		}
		else if (msgFromGraphics.length() == 3) // result for pawn promotion (format = "{file}{rank}{type}")
		{
			result = board.promotePiece(board.getPiece(msgFromGraphics.substr(0, 2)), msgFromGraphics[2]);
			// send the result code to graphics
			// constants for the codes can be found in Piece.h
			strcpy_s(msgToGraphics, std::to_string(result).c_str());
		}
		else
		{
			// access src and dest pieces using the information from the client
			Move* move = new Move(msgFromGraphics.substr(0, 2), msgFromGraphics.substr(2, 2), &board);
			Piece* srcPiece = move->getSrcPiece();
			Piece* destPiece = move->getDestPiece();
			bool isEmpty = destPiece->getType() == EMPTY_PIECE;
			bool whitePlayer = board.getCurrentPlayer().getType() == WHITE_PLAYER;
			// make basic checks, if all basic checks passed, make
			// further checks with the current piece, and send result to graphics
			result = srcPiece->basicValidateMove(board.getCurrentPlayer(), *destPiece);
			if (result == VALID_MOVE)
				result = srcPiece->validateMove(*destPiece);
			int newResult = 0;

			// perform the actual "move"
			if (result == VALID_MOVE || result == VALID_PAWN_PROMOTION || result == VALID_EN_PASSANT || result == VALID_CASTLE)
			{
				// update source piece location + update result incase of "chess"/"self chess"
				newResult = board.movePiece(*srcPiece, *destPiece, *move);

				if (newResult == VALID_MOVE || newResult == VALID_CHESS)
				{
					if (result == VALID_EN_PASSANT)
					{
						char destCol = destPiece->getLocation()[0];
						int rowOffset = whitePlayer ? -1 : 1;
						string capturedPieceLocation = destPiece->getLocation();
						capturedPieceLocation[1] += rowOffset;
						Piece* capturedPiece = board.getPiece(capturedPieceLocation);
						capturedPiece->setCaptured(true);
						move->setCaptured(capturedPiece);
						move->setEnPassant(true);
						board.getBoard()[Board::getIndex(capturedPieceLocation)] = EMPTY_PIECE;
					}
					else if (result == VALID_CASTLE)
					{
						char row = move->getDest()[1];
						int srcCol = (move->getDest()[0] - 'a') == POSSIBLE_KINGSIDE_CASTLE_COL ? KINGSIDE_ROOK_COL : QUEENSIDE_ROOK_COL;
						int destCol = srcCol == KINGSIDE_ROOK_COL ? AFTER_KINGSIDE_CASTLE_ROOK : AFTER_QUEENSIDE_CASTLE_ROOK;
						string destLocation = string(1, (char)(destCol + 'a')) + row;
						Piece* rook = board.getPiece(string(1, (char)(srcCol + 'a')) + row);
						board.getBoard()[rook->getIndex()] = EMPTY_PIECE;
						board.getBoard()[Board::getIndex(destLocation)] = rook->getIdentifier();
						rook->setLocation(destLocation);
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
			strcpy_s(msgToGraphics, std::to_string(result).c_str());
		}

		// return result to graphics
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}


	// send history to graphics
	string history = board.getMoveHistory();
	strcpy_s(msgToGraphics, history.c_str());
	p.sendMessageToGraphics(msgToGraphics);

	// free program's used memory
	p.close();
	msgFromGraphics.clear();

	return 0;
}