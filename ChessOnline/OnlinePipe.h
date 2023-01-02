#pragma once
#pragma warning (disable : 6276 4477 6054)
#pragma region Includes
#define _CRT_SECURE_NO_WARNINGS
#include "Socket.h"
#include <string>
#include <thread>
#include <vector>
#include <mutex>

#pragma endregion

class OnlinePipe;
typedef void (*handler)(SOCKET, SOCKET, OnlinePipe&);

class OnlinePipe
{
private:
	Socket _socket;

	// Create a vector to store the threads
	std::vector<std::thread*> _clientThreads;
public:

	OnlinePipe(handler handleGame)
	{
		_socket = Socket(18079);
		SOCKET serverSocket = _socket.getServerSocket();

		SOCKET cachedClient = 0;

		// Create a mutex to synchronize access to the vector
		std::mutex clientThreadsMutex;

		while (true)
		{
			if (_clientThreads.size() < 10)
			{
				SOCKET clientSocket1, clientSocket2;

				std::cout << currentDateTime() << "Ready to accept a pair of connections." << std::endl;

				clientSocket1 = cachedClient != 0 ? cachedClient : _socket.acceptClient();
				cachedClient = 0;

				std::cout << currentDateTime() << "First client connected! Waiting for the second to make a pair..." << std::endl;

				clientSocket2 = _socket.acceptClient();

				// check if the first client hasnt made a disconnect during the wait time for the second client
				if (!_socket.clientConnected(clientSocket1))
				{
					cachedClient = clientSocket2;
					std::cout << currentDateTime() << "First client disconnected while matchmaking, waiting for another client to create a match..." << std::endl;
					continue;
				}

				std::cout << currentDateTime() << "Second client connected! Starting game..." << std::endl;

				// Lock the mutex to prevent concurrent access to the vector
				std::lock_guard<std::mutex> guard(clientThreadsMutex);

				// Create a new thread to handle the connection
				std::thread* thread = new std::thread([handleGame, clientSocket1, clientSocket2, this]() {
					handleGame(clientSocket1, clientSocket2, *this);
					});
				_clientThreads.push_back(thread);
			}
		}
	}

	const Socket& getSocket() const
	{
		return _socket;
	}

	std::vector<std::thread*>& getThreads()
	{
		return _clientThreads;
	}

	bool sendMessageToGraphics(SOCKET& client, const std::string& msg)
	{
		return sendMessageToGraphics(client, (char*)msg.c_str());
	}

	bool sendMessageToGraphics(SOCKET& client, char* msg)
	{
		return _socket.sendMsg(client, msg);
	}

	std::string getMessageFromGraphics(SOCKET& client)
	{
		string result = "";
		_socket.recvMsg(client, result);

		return result;
	}

	bool getMessageFromGraphics(SOCKET& client, string& out)
	{
		return _socket.recvMsg(client, out);
	}
};
