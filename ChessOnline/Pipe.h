#pragma once
#pragma warning (disable : 6276 4477 6054)
#pragma region Includes
#include "Socket.h"
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include "Player.h"

#pragma endregion

class Pipe
{
private:
	Socket _socket;
public:

	Pipe(void (*handleClient)(SOCKET, SOCKET, Pipe*))
	{
		_socket = Socket(5555);
		SOCKET serverSocket = _socket.getServerSocket();

		SOCKET cachedClient = 0;

		// Create a vector to store the threads
		std::vector<std::thread> clientThreads;
		// Create a mutex to synchronize access to the vector
		std::mutex clientThreadsMutex;

		while (true)
		{
			if (clientThreads.size() < 10)
			{
				SOCKET clientSocket1, clientSocket2;

				std::cout << "Ready to accept a pair of connections." << std::endl;

				clientSocket1 = cachedClient != 0 ? cachedClient : _socket.acceptClient();
				cachedClient = 0;

				std::cout << "First client connected! Waiting for the second to make a pair..." << std::endl;

				clientSocket2 = _socket.acceptClient();

				// check if the first client hasnt made a disconnect during the wait time for the second client
				if (!_socket.clientConnected(clientSocket1))
				{
					cachedClient = clientSocket2;
					std::cout << "First client disconnected while matchmaking, waiting for another client to create a match..." << std::endl;
					continue;
				}

				std::cout << "Second client connected! Starting game..." << std::endl;


				// Lock the mutex to prevent concurrent access to the vector
				std::lock_guard<std::mutex> guard(clientThreadsMutex);

				// Create a new thread to handle the connection
				clientThreads.push_back(std::thread([handleClient, clientSocket1, clientSocket2, this]() {
					handleClient(clientSocket1, clientSocket2, this);
					}));
			}
			else
			{
				// wait for all 10 games to finish before accepting another 10 games
				for (std::thread& t : clientThreads) {
					t.join();
				}
				clientThreads.clear();
			}
		}
	}

	const Socket& getSocket() const
	{
		return _socket;
	}

	bool sendMessageToGraphics(SOCKET client, const std::string& msg)
	{
		return sendMessageToGraphics(client, (char*)msg.c_str());
	}

	bool sendMessageToGraphics(SOCKET client, char* msg)
	{
		return _socket.sendMsg(client, msg);
	}

	std::string getMessageFromGraphics(SOCKET client)
	{
		string result = "";
		_socket.recvMsg(client, result);

		return result;
	}
};
