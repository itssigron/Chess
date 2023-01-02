#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Winsock2.h> 

using std::string;
const std::string currentDateTime();

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
			std::cerr << currentDateTime() << "WSAStartup failed: " << result << std::endl;
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
			std::cerr << currentDateTime() << "bind failed: " << WSAGetLastError() << std::endl;
			closesocket(_serverSocket);
			WSACleanup();
			throw "binding failed";
		}

		// Start listening for connections
		result = listen(_serverSocket, SOMAXCONN);
		if (result == SOCKET_ERROR)
		{
			std::cerr << currentDateTime() << "listen failed: " << WSAGetLastError() << std::endl;
			closesocket(_serverSocket);
			WSACleanup();
			throw "listening socket failed";
		}

		std::cout << currentDateTime() << "Successfully initiated socket." << std::endl;
	}

	const SOCKET getServerSocket() const
	{
		return _serverSocket;
	}

	bool clientConnected(SOCKET clientSocket) const
	{
		return send(clientSocket, NULL, 0, 0) != SOCKET_ERROR;
	}

	SOCKET acceptClient(bool forceValid = true, int maxTries = 5) const
	{

		// Accept a connection from a client
		sockaddr_in clientAddr = {};
		int clientAddrSize = sizeof(clientAddr);
		SOCKET clientSocket = 0;
		int tries = 1;

		// only run a single iteration
		if (forceValid == false)
		{
			maxTries = 1;
		}

		do
		{
			clientSocket = accept(_serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
		} while (clientSocket == -1 && tries++ != maxTries); // loop until valid connection or max tries reached

		return clientSocket;
	}

	bool sendMsg(SOCKET client, const char* message) const
	{
		char* newMsg = new char[strlen(message) + 2]; // extra for dot and extra for null
		strcpy_s(newMsg, strlen(message) + 2, message);
		newMsg[strlen(message)] = '.';
		newMsg[strlen(message) + 1] = 0;

		int result = send(client, newMsg, (int)strlen(newMsg), 0);

		if (result == SOCKET_ERROR)
		{
			std::cerr << currentDateTime() << "send failed: " << WSAGetLastError() << std::endl;
			delete[] newMsg;
			return false;
		}

		std::cout << currentDateTime() << "Sent: " << newMsg << std::endl;
		delete[] newMsg;

		return true;
	}

	bool sendMsg(SOCKET client, string message) const
	{
		return sendMsg(client, message.c_str());
	}

	bool recvMsg(SOCKET client, string& out) const
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
				std::cerr << currentDateTime() << "recv failed: " << WSAGetLastError() << std::endl;
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
			std::cout << currentDateTime() << "Received: " << result << std::endl;
		}

		return !failed;
	}

	void close()
	{

		// Close the server socket
		closesocket(_serverSocket);

		// Clean up Winsock2
		WSACleanup();
	}
};