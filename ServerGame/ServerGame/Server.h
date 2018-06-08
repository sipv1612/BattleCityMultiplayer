#ifndef _SERVER_H_
#define _SERVER_H_

#include <WinSock2.h>
#include <windows.h>
#include "Define.h"



#define PORT 5150
#define DATA_BUFSIZE 8192

	typedef struct _SOCKET_INFORMATION {
		CHAR Buffer[DATA_BUFSIZE];
		WSABUF DataBuf;
		WSABUF DataBufSend;
		SOCKET Socket;
		OVERLAPPED Overlapped;
		DWORD BytesSEND; 
		DWORD BytesRECV;
	} SOCKET_INFORMATION, *LPSOCKET_INFORMATION;

	bool initServer();
	// Prototypes
	BOOL CreateSocketInformation(SOCKET s);
	void FreeSocketInformation(DWORD Index);
	void runserver();
	bool Send( UPDATE_WORLD world);
	void Packing(UPDATE_WORLD world, LPSOCKET_INFORMATION socket);

#endif // !_SERVER_H_
