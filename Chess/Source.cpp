/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Board.h"

using std::cout;
using std::endl;
using std::string;


int main()
{
	// enable virtual terimal processing (ansi color codes)
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	srand(time_t(NULL));
	Pipe p;
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
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return 0;
		}
	}


	// the first message to the graphics will be our board
	char msgToGraphics[1024] = "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1";
	Board board = Board(string(msgToGraphics)); //initialize our Board class

	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		//access src and dest pieces using the information from the client
		Piece& srcPiece = board.getPiece(msgFromGraphics.substr(0, 2));
		Piece& destPiece = board.getPiece(msgFromGraphics.substr(2, 2));

		// print all valid moves this src can do to console for debugging
		board.printAllValidLocations(srcPiece);
		
		// make basic checks, if all basic checks passed, make
		// further checks with the current piece, and send result to graphics
		int result = srcPiece.basicValidateMove(board.getCurrentPlayer(), destPiece);
		if (result == VALID_MOVE) result = srcPiece.validateMove(destPiece);

		// perform the actual "move"
		if (result == VALID_MOVE)
		{
			// update source piece location
			board.movePiece(srcPiece, destPiece);
		}

		// send the result code to graphics
		// constants for the codes can be found in Piece.h
		msgToGraphics[0] = result + '0';
		msgToGraphics[1] = 0; //end string

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
	return 0;
}