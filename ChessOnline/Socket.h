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
		// Calculate the message size
		uint16_t messageSize = strlen(message);

		// Convert the message size to network byte order
		char* data = reinterpret_cast<char*>(&messageSize);

		char* newMsg = new char[sizeof(uint16_t) + messageSize + 1]; // message size + message + extra for null
		memcpy(newMsg, &messageSize, sizeof(uint16_t));
		memcpy(newMsg + sizeof(uint16_t), message, messageSize);

		newMsg[sizeof(uint16_t) + messageSize] = 0;

		int result = send(client, newMsg, sizeof(uint16_t) + messageSize, 0);

		if (result == SOCKET_ERROR)
		{
			std::cerr << currentDateTime() << "send failed: " << WSAGetLastError() << std::endl;
			delete[] newMsg;
			return false;
		}

		std::cout << currentDateTime() << "Sent: " << (newMsg + sizeof(uint16_t)) << std::endl;
		delete[] newMsg;

		return true;
	}

	bool sendMsg(SOCKET client, string message) const
	{
		return sendMsg(client, message.c_str());
	}

	bool recvMsg(SOCKET client, std::string& out) const
	{
		uint16_t messageSize = 0;

		// Receive the size header (first 2 bytes)
		int bytesReceived = recv(client, reinterpret_cast<char*>(&messageSize), sizeof(uint16_t), 0);
		if (bytesReceived == SOCKET_ERROR || bytesReceived != sizeof(uint16_t))
		{
			std::cerr << currentDateTime() << "recv size header failed: " << WSAGetLastError() << std::endl;
			return false;
		}

		// Receive the entire message based on the size received
		std::string buffer(messageSize, '\0');
		bytesReceived = recv(client, const_cast<char*>(buffer.c_str()), messageSize, 0);

		if (bytesReceived == SOCKET_ERROR || bytesReceived != messageSize)
		{
			std::cerr << currentDateTime() << "recv message failed: " << WSAGetLastError() << std::endl;
			return false;
		}

		out = buffer;
		std::cout << currentDateTime() << "Received: " << out << std::endl;

		return true;
	}

	void close()
	{

		// Close the server socket
		closesocket(_serverSocket);

		// Clean up Winsock2
		WSACleanup();
	}
};