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
	Socket socket;
public:

	Pipe(void (*handleClient)(SOCKET, SOCKET, Pipe*))
	{
		SOCKET serverSocket = socket.getServerSocket();


		// Create a vector to store the threads
		std::vector<std::thread> clientThreads;
		// Create a mutex to synchronize access to the vector
		std::mutex clientThreadsMutex;

		while (true)
		{
			if (clientThreads.size() < 10)
			{
				std::cout << "Ready to accept a pair of connections." << std::endl;

				// Accept a connection from a client
				sockaddr_in clientAddr;
				int clientAddrSize = sizeof(clientAddr);
				SOCKET clientSocket1, clientSocket2;

				do
				{
					clientSocket1 = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
				} while (clientSocket1 == -1); // loop until valid connection

				std::cout << "First client connetected! Waiting for the second to make a pair..." << std::endl;

				do
				{
					clientSocket2 = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
				} while (clientSocket2 == -1); // loop until valid connection

				std::cout << "Second client connetected! Starting game..." << std::endl;

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

	bool sendMessageToGraphics(SOCKET client, const std::string& msg)
	{
		return sendMessageToGraphics(client, (char*)msg.c_str());
	}

	bool sendMessageToGraphics(SOCKET client, char* msg)
	{
		return socket.sendMsg(client, msg);
	}

	std::string getMessageFromGraphics(SOCKET client)
	{
		string result = "";
		socket.recvMsg(client, result);

		return result;
	}
};
