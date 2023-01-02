#include "OnlinePipe.h"
#include <iostream>

#define WHITE_PLAYER "0"
#define BLACK_PLAYER "1"

using std::cout;
using std::endl;
using std::string;

void handleGame(SOCKET whitePlayer, SOCKET blackPlayer, OnlinePipe* pipe);
void swap(SOCKET& client, SOCKET& enemyClient);

int main(int argc, char* argv[])
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	OnlinePipe p(handleGame);

	return 0;
}

void handleGame(SOCKET whitePlayer, SOCKET blackPlayer, OnlinePipe* pipe)
{
	OnlinePipe& p = *pipe;
	string msgFromGraphics = "";
	SOCKET client = whitePlayer; // white player starts
	SOCKET enemyClient = blackPlayer;

	// let clients know which side they are
	p.sendMessageToGraphics(whitePlayer, WHITE_PLAYER);
	p.sendMessageToGraphics(blackPlayer, BLACK_PLAYER);

	do
	{
		msgFromGraphics = p.getMessageFromGraphics(client);

		// length of a valid move or quit (left in the middle of the game)
		if (msgFromGraphics.length())
		{
			// let enemy client know so he can apply it aswell
			p.sendMessageToGraphics(enemyClient, msgFromGraphics);

			// swap sockets
			swap(client, enemyClient);
		}
	} while (msgFromGraphics != "quit" && msgFromGraphics != "win" && p.getSocket().clientConnected(client));
}

void swap(SOCKET& client, SOCKET& enemyClient)
{
	SOCKET temp = client;
	client = enemyClient;
	enemyClient = temp;
}