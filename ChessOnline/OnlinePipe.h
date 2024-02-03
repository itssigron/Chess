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
	std::vector<std::thread> _clientThreads;
	// Create a mutex to synchronize access to the vector
	std::mutex _clientThreadsMutex;

public:

	OnlinePipe(handler gameHandler)
	{
		_socket = Socket(18079);
		SOCKET serverSocket = _socket.getServerSocket();

		SOCKET cachedClient = 0;


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

				addGame(clientSocket1, clientSocket2, gameHandler);
			}
		}
	}

	void addGame(SOCKET clientSocket1, SOCKET clientSocket2, handler gameHandler)
	{
		// Lock the mutex to prevent concurrent access to the vector
		std::lock_guard<std::mutex> guard(_clientThreadsMutex);

		// Create a new thread to handle the connection
		std::thread thread = std::thread([=]() {
			gameHandler(clientSocket1, clientSocket2, *this);
			});

		_clientThreads.push_back(std::move(thread));
	}

	void removeGame(std::thread::id threadId)
	{
		// Lock the mutex to prevent concurrent access to the vector
		std::lock_guard<std::mutex> guard(_clientThreadsMutex);

		// remove the specified thread from the threads vector by its id
		auto threadIt = std::find_if(_clientThreads.begin(), _clientThreads.end(), [=](std::thread& t) { return (t.get_id() == threadId); });

		// make sure the thread is found
		if (threadIt != _clientThreads.end())
		{
			threadIt->detach();
			_clientThreads.erase(threadIt);
		}
	}

	const Socket& getSocket() const
	{
		return _socket;
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
