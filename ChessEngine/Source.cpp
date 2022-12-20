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

	// start the client
	// system("start ChessClient.exe");

	// Sleep(1000); // wait for client to start

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
	char msgToGraphics[1024] = "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0";
	Board board = Board(string(msgToGraphics)); // initialize our Board class
	int result = 0;

	p.sendMessageToGraphics(msgToGraphics); // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit" && msgFromGraphics != "") // an empty string can be considered as a "quit"
	{
		if (msgFromGraphics == "print-history") // graphics wants to print game history, lets both print and send back history as well
		{
			//std::cout << "Game's moves history: " << board.getAllMoves() << std::endl;
			//strcpy_s(msgToGraphics, board.getAllMoves().c_str());
		}
		else if (msgFromGraphics == "undo")
		{
			Move* move = board.undoMove();
			char identifier = move == nullptr ? ' ' :
				move->getCaptured() == nullptr ? EMPTY_PIECE : move->getCaptured()->getIdentifier();

			// format is {dest}{src}{captured identifier if any} will undo move in graphics
			strcpy_s(msgToGraphics, move == nullptr ? "" : (move->getDest() + move->getSrc() + identifier).c_str());
			if (move != nullptr && move->getCaptured() != nullptr)
			{
				move->setCaptured(nullptr); // un-capture
			}
		}
		else if (msgFromGraphics == "redo")
		{
			Move* move = board.redoMove();
			strcpy_s(msgToGraphics, move == nullptr ? "" : (move->getSrc() + move->getDest()).c_str());
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

			// make basic checks, if all basic checks passed, make
			// further checks with the current piece, and send result to graphics
			result = srcPiece->basicValidateMove(board.getCurrentPlayer(), *destPiece);
			if (result == VALID_MOVE)
				result = srcPiece->validateMove(*destPiece);
			int newResult = 0;

			// perform the actual "move"
			if (result == VALID_MOVE || result == VALID_PAWN_PROMOTION)
			{
				// update source piece location + update result incase of "chess"
				newResult = board.movePiece(*srcPiece, *destPiece);
				if (newResult == VALID_MOVE || newResult == VALID_CHESS)
				{
					if (!isEmpty)
					{
						move->setCaptured(destPiece);
					}
					board.pushMove(move);
				}
				// Board::movePiece doesnt check for pawn promotion, so this condition fixes this bug
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

	// dump history to terminal
	//std::cout << "Game's moves history: " << board.getAllMoves() << std::endl;

	std::cout << "Goodbye!" << std::endl;

	// free program's used memory
	p.close();
	msgFromGraphics.clear();

	system("pause"); // wait until user presses a key

	return 0;
}