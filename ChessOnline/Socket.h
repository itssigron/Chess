#include <iostream>
#include <cstring>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Winsock2.h> // Use Winsock2 instead of sys/socket.h
#include <exception>

using std::string;

class Socket
{
private:
	SOCKET _serverSocket;
public:
	Socket()
	{
		_serverSocket = 0;
	}
	Socket(int port)
	{
		// Initialize Winsock2
		WSADATA wsaData;
		int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

		if (result != 0)
		{
			std::cerr << "WSAStartup failed: " << result << std::endl;
			throw "WSAStartup failed";
		}

		// Create a socket
		_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// Set up the server address structure
		sockaddr_in serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(port);
		serverAddr.sin_addr.S_un.S_addr = inet_addr("0.0.0.0"); // Listen on all available interfaces

		// Bind the socket to the address and port
		result = bind(_serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
		if (result == SOCKET_ERROR)
		{
			std::cerr << "bind failed: " << WSAGetLastError() << std::endl;
			closesocket(_serverSocket);
			WSACleanup();
			throw "binding failed";
		}

		// Start listening for connections
		result = listen(_serverSocket, SOMAXCONN);
		if (result == SOCKET_ERROR)
		{
			std::cerr << "listen failed: " << WSAGetLastError() << std::endl;
			closesocket(_serverSocket);
			WSACleanup();
			throw "listening socket failed";
		}

		std::cout << "Successfully initiated socket." << std::endl;
	}

	SOCKET getServerSocket()
	{
		return _serverSocket;
	}

	bool sendMsg(SOCKET client, const char* message)
	{
		char* newMsg = new char[strlen(message) + 2]; // extra for dot and extra for null
		strcpy_s(newMsg, strlen(message) + 2, message);
		newMsg[strlen(message)] = '.';
		newMsg[strlen(message) + 1] = 0;

		int result = send(client, newMsg, strlen(newMsg), 0);

		if (result == SOCKET_ERROR)
		{
			std::cerr << "send failed: " << WSAGetLastError() << std::endl;
			delete[] newMsg;
			return false;
		}

		std::cout << "Sent: " << newMsg << std::endl;
		delete[] newMsg;

		return true;
	}

	bool sendMsg(SOCKET client, string message)
	{
		return sendMsg(client, message.c_str());
	}

	bool recvMsg(SOCKET client, string& out)
	{
		std::string result = "";

		bool finished = false;
		bool failed = false;

		// Receive messages until a dot is encountered
		while (finished == false)
		{
			// Receive a single byte
			char data[1];
			int bytesReceived = recv(client, data, 1, 0);
			if (bytesReceived == SOCKET_ERROR || bytesReceived == 0)
			{
				std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
				failed = true;
				finished = true;
			}
			// Check if the message is complete (ends with a dot)
			if (data[0] == '.')
			{
				finished = true;
			}
			else
			{
				// Append the received byte to the message
				result += data[0];
			}
		}

		if (!failed)
		{
			out = result;
			std::cout << "Received: " << result << std::endl;
		}

		return failed;
	}

	void close()
	{

		// Close the server socket
		closesocket(_serverSocket);

		// Clean up Winsock2
		WSACleanup();
	}
};