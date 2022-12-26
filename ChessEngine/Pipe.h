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
#pragma region Includes
#include "stdafx.h"

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

public:

	Pipe()
	{
		// Prepare the pipe name
		pipeNumber = 1;
		lstrcpyW(strPipeName, (LPWSTR)TEXT("\\\\.\\pipe\\chessPipe"));
		lstrcatW(strPipeName, (LPWSTR)std::to_string(pipeNumber).c_str());
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


		if (GetLastError() == ERROR_PIPE_BUSY)
		{
			lstrcpyW(strPipeName, (LPWSTR)TEXT("\\\\.\\pipe\\chessPipe"));
			lstrcatW(strPipeName, (LPWSTR)std::to_string(++pipeNumber).c_str());

			result = false;
		}
		// Break if the pipe handle is valid. 
		else if (hPipe != INVALID_HANDLE_VALUE)
		{
			result = true;
		}
		else if (GetLastError() != ERROR_PIPE_BUSY || !WaitNamedPipe((LPCSTR)strPipeName, 5000))
		{
			_tprintf(_T("Unable to open named pipe %s w/err 0x%08lx\n"), strPipeName, GetLastError());
			result = false;
		}
		else
		{
			#ifdef _DEBUG
				_tprintf(_T("The named pipe, %s, is connected.\n"), strPipeName);
			#endif	
		}

		return result;

	}

	bool sendMessageToGraphics(std::string msg)
	{
		return sendMessageToGraphics((char*)msg.c_str());
	}

	bool sendMessageToGraphics(char* msg)
	{
		//char ea[] = "SSS";
		char* chRequest = msg;	// Client -> Server
		DWORD cbBytesWritten, cbRequestBytes;

		// Send one message to the pipe.
		cbRequestBytes = sizeof(TCHAR) * (lstrlen((chRequest)) + 1);

		BOOL bResult = WriteFile(			// Write to the pipe.
			hPipe,						// Handle of the pipe
			chRequest,					// Message to be written
			cbRequestBytes,				// Number of bytes to write
			&cbBytesWritten,			// Number of bytes written
			NULL);						// Not overlapped 

		if (!bResult/*Failed*/ || cbRequestBytes != cbBytesWritten/*Failed*/)
		{
			#ifdef _DEBUG
				_tprintf(_T("WriteFile failed w/err 0x%08lx\n"), GetLastError());
			#endif		
			return false;
		}

		#ifdef _DEBUG
			_tprintf(_T("Sends %ld bytes; Message: \"%s\"\n"),
			cbBytesWritten, chRequest);
		#endif

		return true;

	}

	std::string getMessageFromGraphics()
	{
		DWORD cbBytesRead;
		DWORD cbReplyBytes;
		TCHAR chReply[BUFFER_SIZE];		// Server -> Client

		cbReplyBytes = sizeof(TCHAR) * BUFFER_SIZE;
		BOOL bResult = ReadFile(			// Read from the pipe.
			hPipe,					// Handle of the pipe
			chReply,				// Buffer to receive the reply
			cbReplyBytes,			// Size of buffer 
			&cbBytesRead,			// Number of bytes read 
			NULL);					// Not overlapped 

		if (!bResult && GetLastError() != ERROR_MORE_DATA)
		{
			#ifdef _DEBUG
				_tprintf(_T("ReadFile failed w/err 0x%08lx\n"), GetLastError());
			#endif
			return "";
		}

		#ifdef _DEBUG
			_tprintf(_T("Receives %ld bytes; Message: \"%s\"\n"),
			cbBytesRead, chReply);
		#endif	
		std::string s = chReply;
		return s;

	}

	void close()
	{
		CloseHandle(hPipe);
	}

};
