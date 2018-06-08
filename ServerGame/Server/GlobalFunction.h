#pragma once
#include "GameMgr.h"
#include "GlobalVariable.h"
BOOL CreateSocketInformation(SOCKET s, int* numOfPlayer)
{
	LPSOCKET_INFORMATION SI;

	printf("Accepted socket number %d\n", s);

	if ((SI = (LPSOCKET_INFORMATION)GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION))) == NULL)
	{
		printf("GlobalAlloc() failed with error %d\n", GetLastError());
		return FALSE;
	}
	else
		printf("GlobalAlloc() for SOCKET_INFORMATION is OK!\n");

	// Prepare SocketInfo structure for use
	SI->socket = s;
	SI->bytesSEND = 0;
	SI->bytesRECV = 0;

	socketArray[*numOfPlayer] = SI;
	(*numOfPlayer)++;
	return(TRUE);
}

void FreeSocketInformation(DWORD Index, int* numOfPlayer)
{
	LPSOCKET_INFORMATION SI = socketArray[Index];
	DWORD i;

	closesocket(SI->socket);
	printf("Closing socket number %d\n", SI->socket);
	GlobalFree(SI);

	// Squash the socket array
	for (i = Index; i < (*numOfPlayer); i++)
	{
		socketArray[i] = socketArray[i + 1];
	}

	(*numOfPlayer)--;
}
void Packing(UPDATE_WORLD world, LPSOCKET_INFORMATION socket)
{

	/*if (!(world.allBrick.empty() && world.allBullet.empty() && world.allTank.empty()))
	{
		char *buffer;
		int _size;
		int sizePlayer;
		int sizeBrick;
		int sizeBullet;
		sizePlayer = world.allTank.size();
		sizeBrick = world.allBrick.size();
		sizeBullet = world.allBullet.size();
		_size = sizePlayer * sizeof TANK_STATE + world.allBrick.size() * sizeof BRICK_WORLD + sizeBullet * sizeof BULLET_STATE + 4 * sizeof(int);
		buffer = new char[_size];
		memcpy(buffer, &_world.teamWin, sizeof(int));
		memcpy(buffer + sizeof(int), &sizePlayer, sizeof(int));
		memcpy(buffer + 2 * sizeof(int), &sizeBrick, sizeof(int));
		memcpy(buffer + 3 * sizeof(int), &sizeBullet, sizeof(int));
		for (int i = 0; i < sizePlayer; i++)
		{
			memcpy(buffer + 4 * sizeof(int) + i * sizeof TANK_STATE, world.allTank[i], sizeof TANK_STATE);
		}
		for (int i = 0; i < sizeBrick; i++)
		{
			memcpy(buffer + 4 * sizeof(int) + sizePlayer * sizeof TANK_STATE + i * sizeof BRICK_WORLD, world.allBrick[i], sizeof(BRICK_WORLD));
		}
		for (int i = 0; i < sizeBullet; i++)
		{
			memcpy(buffer + 4 * sizeof(int) + sizePlayer * sizeof TANK_STATE + sizeBrick * sizeof BRICK_WORLD + i * sizeof BULLET_STATE, world.allBullet[i], sizeof(BULLET_STATE));
		}
		socket->dataBufSend.buf = new char[_size];
		socket->dataBufSend.buf = buffer;
		socket->dataBufSend.len = _size;
	}*/

}

void SendData()
{
	if (LPDataSendBuffer <= 4)
		return;
	for (int i = 0; i < numOfPlayer && Total > 0; i++)
	{
		if (FD_ISSET(socketArray[i]->socket, &WriteSet))
		{
			//printf("data %d before send: %s\n", i, dataSend[i]);
			//SendByte(i);
			memcpy(dataSendBuffer, &LPDataSendBuffer, sizeof(int));
			socketArray[i]->dataBufSend.buf = dataSendBuffer;
			socketArray[i]->dataBufSend.len = LPDataSendBuffer;

			printf("%d \n", LPDataSendBuffer);
			if (WSASend(socketArray[i]->socket, &(socketArray[i]->dataBufSend), 1, &socketArray[i]->bytesSEND, 0, NULL, NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					printf("WSASend() failed with error %d\n", WSAGetLastError());
					FreeSocketInformation(i, &numOfPlayer);

				}
				/*else
				printf("WSASend() is OK!\n");*/
			}
			else
			{

			}
		}
	}
	LPDataSendBuffer = sizeof(int);
}
void  NetworkProc(void* Data)
{
	SOCKET ListenSocket;
	SOCKET AcceptSocket;
	SOCKADDR_IN InternetAddr;
	WSADATA wsaData;
	INT Ret;
	DWORD i;
	ULONG NonBlock;
	DWORD Flags;
	DWORD SendBytes;
	DWORD RecvBytes;
	DWORD lastTime = 0;
	//int numOfPlayer = 0;
	int LPHead[4];
	for (int i = 0; i < 4; i++)
	{
		LPHead[i] = 0;
	}
	//Init server
	if ((Ret = WSAStartup(0x0202, &wsaData)) != 0)
	{
		printf("WSAStartup() failed with error %d\n", Ret);
		WSACleanup();
		return;
	}
	else
		printf("WSAStartup() is fine!\n");

	// Prepare a socket to listen for connections
	if ((ListenSocket = WSASocketW(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		printf("WSASocket() failed with error %d\n", WSAGetLastError());
		return;
	}
	else
		printf("WSASocket() is OK!\n");

	InternetAddr.sin_family = AF_INET;
	InternetAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	InternetAddr.sin_port = htons(DEFAULT_PORT);

	if (bind(ListenSocket, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
	{
		printf("bind() failed with error %d\n", WSAGetLastError());
		return;
	}
	else
		printf("bind() is OK!\n");

	if (listen(ListenSocket, 4))
	{
		printf("listen() failed with error %d\n", WSAGetLastError());
		return;
	}
	else
		printf("listen() is OK!\n");

	// Change the socket mode on the listening socket from blocking to
	// non-block so the application will not block waiting for requests
	NonBlock = 1;
	if (ioctlsocket(ListenSocket, FIONBIO, &NonBlock) == SOCKET_ERROR)
	{
		printf("ioctlsocket() failed with error %d\n", WSAGetLastError());
		return;
	}
	else
		printf("ioctlsocket() is OK!\n");

	while (!gameEnded)
	{
		if (numOfPlayer < NUM_OF_PLAYER && !gameRunning) // If not enough player
		{
			if ((AcceptSocket = accept(ListenSocket, NULL, NULL)) != INVALID_SOCKET)
			{
				// Set the accepted socket to non-blocking mode so the server will
				// not get caught in a blocked condition on WSASends
				NonBlock = 1;
				if (ioctlsocket(AcceptSocket, FIONBIO, &NonBlock) == SOCKET_ERROR)
				{
					printf("ioctlsocket(FIONBIO) failed with error %d\n", WSAGetLastError());
				}
				else
				{
					printf("ioctlsocket(FIONBIO) is OK!\n");
				}

				CreateSocketInformation(AcceptSocket, &numOfPlayer);
				for (int i = 0; i < numOfPlayer; i++)
				{
					socketArray[i]->dataBuf.buf = socketArray[i]->buffer;
					socketArray[i]->dataBuf.len = DATA_BUFSIZE;
					memcpy(socketArray[i]->buffer, (char*)(&numOfPlayer), sizeof(int));
					send(socketArray[i]->socket, socketArray[i]->buffer, sizeof(int), 0);
				}
			}
			else
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					printf("accept() failed with error %d\n", WSAGetLastError());
				}
			}

		}
		else //If enough player
		{
			gameRunning = true;
			// Prepare the Read and Write socket sets for network I/O notification
			FD_ZERO(&ReadSet);
			FD_ZERO(&WriteSet);

			for (i = 0; i < numOfPlayer; i++)
			{
				FD_SET(socketArray[i]->socket, &WriteSet);
				FD_SET(socketArray[i]->socket, &ReadSet);
			}

			if ((Total = select(0, &ReadSet, &WriteSet, NULL, NULL)) == SOCKET_ERROR)
			{
				printf("select() returned with error %d\n", WSAGetLastError());
			}

			//Receive and send data

			for (i = 0; Total > 0 && i < numOfPlayer; i++)
			{
				// If the ReadSet is marked for this socket then this means data
				// is available to be read on the socket

				if (FD_ISSET(socketArray[i]->socket, &ReadSet))
				{
					Flags = 0;
					if (WSARecv(socketArray[i]->socket, &(socketArray[i]->dataBuf), 1, &socketArray[i]->bytesRECV, &Flags, NULL, NULL) == SOCKET_ERROR)
					{
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							printf("WSARecv() failed with error %d\n", WSAGetLastError());
							//FreeSocketInformation(i, &numOfPlayer);
						}

					}
					else
					{

						{
							EnterCriticalSection(&criticalDataRecv);
							dataRecv[i]->Add(socketArray[i]->dataBuf.buf, socketArray[i]->bytesRECV);
							LeaveCriticalSection(&criticalDataRecv);
						}

					}
				}


			}
		}
	}
}
void GameProc(void* Data)
{
	DWORD frameStart = GetTickCount();
	DWORD timesend = 0;
	float tickPerFrame = (float)1 / 120;
	float dt = 0;
	float dtsend = 0;
	int TimeEnd = 0;

	while (!gameEnded)
	{
		if (gameRunning)
		{
			DWORD now = GetTickCount();
			dt = (float)(now - frameStart) / 1000;
			dtsend = (float)(now - timesend) / 1000;

			if (dt >= tickPerFrame)
			{

				GameMgr::GetInstance()->Update(dt);

				if (dtsend > (float)1 / 30)
				{

					SendData();
					timesend = now;
					/*if (_world.teamWin != 0)
					{
					TimeEnd++;
					if (TimeEnd > 2)
					{
					gameEnded = true;
					}
					}*/
				}
				frameStart = now;
			}
			else
			{
				Sleep((tickPerFrame - dt) * 1000);
				dt = tickPerFrame - dt;
			}
		}

	}
}
