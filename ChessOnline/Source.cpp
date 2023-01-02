#include "OnlinePipe.h"
#include <iostream>

#define WHITE_PLAYER "0"
#define BLACK_PLAYER "1"
#define ISRAEL_TIMEZONE_OFFSET 2
#define EXIT_SUCCESS 0

using std::cout;
using std::endl;
using std::string;

void handleGame(SOCKET whitePlayer, SOCKET blackPlayer, OnlinePipe& pipe);
void handleClient(SOCKET client, SOCKET enemyClient, OnlinePipe& p);

int main(int argc, char* argv[])
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	OnlinePipe p(handleGame);

	return EXIT_SUCCESS;
}

void handleGame(SOCKET whitePlayer, SOCKET blackPlayer, OnlinePipe& p)
{
	std::thread whitePlayerThread = std::thread(handleClient, whitePlayer, blackPlayer, std::ref(p));
	std::thread blackPlayerThread = std::thread(handleClient, blackPlayer, whitePlayer, std::ref(p));

	std::cout << currentDateTime() << "Game started." << std::endl;

	// let clients know which side they are
	p.sendMessageToGraphics(whitePlayer, WHITE_PLAYER);
	p.sendMessageToGraphics(blackPlayer, BLACK_PLAYER);


	// white for clients's threads to finish before finishing the game
	whitePlayerThread.join();
	blackPlayerThread.join();

	std::cout << currentDateTime() << "Game over." << std::endl;

	std::vector<std::thread*>& threads = p.getThreads();
	std::thread::id threadId = std::this_thread::get_id();
	std::thread* th = nullptr;

	// remove the thread from the threads vector
	for (std::thread*& t : threads)
	{
		if (t->get_id() == threadId)
		{
			th = t;
			threads.erase(std::remove(threads.begin(), threads.end(), t), threads.end());
		}
	}
}

void handleClient(SOCKET client, SOCKET enemyClient, OnlinePipe& p)
{
	string msgFromGraphics = "";

	while (msgFromGraphics != "quit" && msgFromGraphics != "win" && p.getMessageFromGraphics(client, msgFromGraphics))
	{
		// if its a valid message and not an empty string (most likely disconnection)
		if (msgFromGraphics.length())
		{
			// let enemy client know so he can apply it aswell
			// and if message failed then just exit the loop since the game should be over
			if (!p.sendMessageToGraphics(enemyClient, msgFromGraphics))
			{
				msgFromGraphics = "quit";
			}
		}
	}
}

const std::string currentDateTime()
{
	// Get the current time
	std::time_t t = std::time(nullptr);

	// Convert the current time to the Israeli timezone (GMT + 2)
	std::tm* tm = std::gmtime(&t);
	tm->tm_hour += ISRAEL_TIMEZONE_OFFSET;
	t = std::mktime(tm);

	// Get the current date and time as a string in the Israeli timezone
	char date_time_str[100];
	std::strftime(date_time_str, sizeof(date_time_str), "%d-%m-%Y %X ", tm);

	return date_time_str;
}