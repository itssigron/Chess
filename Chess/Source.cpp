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
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(1000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return 0;
		}
	}

	ans.clear();

	// the first message to the graphics will be our board with 0 at the end to indicate the WHITE_PLAYER is the starting player
	char msgToGraphics[1024] = "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0";
	Board board = Board(string(msgToGraphics)); // initialize our Board class
	int result = 0;

	p.sendMessageToGraphics(msgToGraphics); // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// source piece selection, meaning we want to send all of its possible moves to graphics
		if (msgFromGraphics.length() == 2)
		{
			Piece *srcPiece = board.getPiece(msgFromGraphics);
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
			Piece *srcPiece = board.getPiece(msgFromGraphics.substr(0, 2));
			Piece *destPiece = board.getPiece(msgFromGraphics.substr(2, 2));

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

	// free program's used memory
	p.close();
	msgFromGraphics.clear();

	return 0;
}