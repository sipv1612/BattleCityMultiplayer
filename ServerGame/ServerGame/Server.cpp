#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Server.h"

extern std::queue<TANK_STATE*> HQueue;
extern UPDATE_WORLD _world;


bool initServer()
{

	
	
	return true;
}



void FreeSocketInformation(DWORD Index)
{
	LPSOCKET_INFORMATION SI = SocketArray[Index];
	DWORD i;

	closesocket(SI->Socket);
	printf("Closing socket number %d\n", SI->Socket);
	GlobalFree(SI);

	// Squash the socket array
	for (i = Index; i < TotalSockets; i++)
	{
		SocketArray[i] = SocketArray[i + 1];
	}

	TotalSockets--;
}

void runserver()
{
	
}


bool Send(UPDATE_WORLD world)
{
	for (i = 0; Total > 0 && i < TotalSockets; i++)
	{
		LPSOCKET_INFORMATION SocketInfo = SocketArray[i];
		// If the WriteSet is marked on this socket then this means the internal
		// data buffers are available for more data

		
		if (FD_ISSET(SocketInfo->Socket, &WriteSet))
		{
			Packing(world, SocketInfo);
			if (WSASend(SocketInfo->Socket, &(SocketInfo->DataBufSend), 1, &SendBytes, 0, NULL, NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					printf("WSASend() failed with error %d\n", WSAGetLastError());
					FreeSocketInformation(i);
					return false;
				}
				else
					printf("WSASend() is OK!\n");
				continue;
			}
		}
			else
			{
				SocketInfo->BytesSEND += SendBytes;
				if (SocketInfo->BytesSEND == SocketInfo->BytesRECV)
				{
					SocketInfo->BytesSEND = 0;
					SocketInfo->BytesRECV = 0;
				}
			}
		}
	

	return true;
}

void Packing(UPDATE_WORLD world, LPSOCKET_INFORMATION socket)
{
	char *buffer;
	int _size;
	unsigned int sizePlayer;

	_size = sizeof TANK_STATE/* + world.allBrick.size() * sizeof BRICK + world.allROBOT.size() * sizeof ROBOT_STATE*/ + sizeof(unsigned int);
	buffer = new char[_size];
	
	sizePlayer = world.allTank.size();
	memcpy(buffer, &sizePlayer, sizeof(unsigned int));
	//for (int i = 0; i < sizePlayer; i++)
	{
		memcpy(buffer + sizeof(unsigned int), world.allTank.at(0), sizeof TANK_STATE);
	}



	socket->DataBufSend.buf = new char[_size];
	//memcpy(socket->DataBufSend.buf, buffer, _size);
	socket->DataBufSend.buf = buffer;
	socket->DataBufSend.len = _size;
}
