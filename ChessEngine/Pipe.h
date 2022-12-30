/****************************** Module Header ******************************\
* Module Name:	CppNamedPipeClient.cpp
* Project:		CppNamedPipeClient
* Copyright (c) Microsoft Corporation.
*
* Named pipe is a mechanism for one-way or bi-directional inter-process
* communication between the pipe server and one or more pipe clients in the
* local machine or across the computers in the intranet:
*
* PIPE_ACCESS_INBOUND:
* Client (GENERIC_WRITE) ---> Server (GENERIC_READ)
*
* PIPE_ACCESS_OUTBOUND:
* Client (GENERIC_READ) <--- Server (GENERIC_WRITE)
*
* PIPE_ACCESS_DUPLEX:
* Client (GENERIC_READ or GENERIC_WRITE, or both) <-->
* Server (GENERIC_READ and GENERIC_WRITE)
*
* This sample demonstrates a named pipe client that attempts to connect to
* the pipe server, \\.\pipe\HelloWorld, with the GENERIC_READ and
* GENERIC_WRITE permissions. The client writes a message to the pipe server
* and receive its response.
*
* This source is subject to the Microsoft Public License.
* See http://www.microsoft.com/opensource/licenses.mspx#Ms-PL.
* All other rights reserved.
*
* History:
* * 1/11/2009 11:20 PM Jialiang Ge Created
\***************************************************************************/

#pragma once
#pragma warning (disable : 6276 4477 6054)
#pragma region Includes
#include "stdafx.h"
#include "Socket.h"
#include <windows.h>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#pragma endregion

#define BUFFER_SIZE		1024 // 1K

class Pipe
{
private:
	HANDLE hPipe;
	wchar_t strPipeName[20];
	int pipeNumber;
	Socket socket;
	SOCKET clientSocket;

public:

	Pipe()
	{
		hPipe = nullptr;
		// Prepare the pipe name
		//pipeNumber = 1;
		//lstrcpyW(strPipeName, (LPWSTR)TEXT("\\\\.\\pipe\\chessPipe"));
		//lstrcatW(strPipeName, (LPWSTR)std::to_string(pipeNumber).c_str());
		SOCKET serverSocket = socket.getServerSocket();

		std::cout << "Ready to accept a connection." << std::endl;

		// Accept a connection from a client
		sockaddr_in clientAddr;
		int clientAddrSize = sizeof(clientAddr);
		clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
	}

	bool connect()
	{
		bool result = true;

		hPipe = CreateFile(
			(LPCSTR)strPipeName,			// Pipe name 
			GENERIC_READ |			// Read and write access 
			GENERIC_WRITE,
			0,						// No sharing 
			NULL,					// Default security attributes
			OPEN_EXISTING,			// Opens existing pipe 
			0,						// Default attributes 
			NULL);					// No template file 


		if (GetLastError() == ERROR_PIPE_BUSY) // pipe is taken, connect to a different one
		{
			lstrcpyW(strPipeName, (LPWSTR)TEXT("\\\\.\\pipe\\chessPipe"));
			lstrcatW(strPipeName, (LPWSTR)std::to_string(++pipeNumber).c_str());

			result = false;
		}
		else if (hPipe != INVALID_HANDLE_VALUE) // pipe is valid and connected
		{
			result = true;
		}
		else if (GetLastError() != ERROR_PIPE_BUSY || !WaitNamedPipe((LPCSTR)strPipeName, 0))
		{
			_tprintf(_T("Unable to open named pipe %ls w/err 0x%08lx\n"), strPipeName, GetLastError());
			result = false;
		}

		return result;

	}

	bool sendMessageToGraphics(const std::string& msg)
	{
		return sendMessageToGraphics((char*)msg.c_str());
	}

	bool sendMessageToGraphics(char* msg)
	{
		return socket.sendMsg(clientSocket, msg);
	}

	std::string getMessageFromGraphics()
	{
		string result = "";
		socket.recvMsg(clientSocket, result);

		return result;
	}

	void close()
	{
		CloseHandle(hPipe);
	}

};
