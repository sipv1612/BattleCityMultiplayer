#include "Client.h"

Client::Client()
{
}

Client::~Client()
{
}

bool Client::initClient()
{
	strcpy_s(szServer, sizeof(szServer), "127.0.0.1");
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		CCLOG("Failed to load Winsock library! Error %d\n", WSAGetLastError());
		return false;
	}
	else
		CCLOG("Winsock library loaded successfully!\n");

	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == INVALID_SOCKET)
	{
		CCLOG("socket() failed with error code %d\n", WSAGetLastError());
		return false;
	}
	else
		CCLOG("socket() looks fine!\n");
	server.sin_family = AF_INET;
	server.sin_port = htons(5150);
	server.sin_addr.s_addr = inet_addr(szServer);
	if (server.sin_addr.s_addr == INADDR_NONE)
	{
		host = gethostbyname(szServer);
		if (host == NULL)
		{
			CCLOG("Unable to resolve server %s\n", szServer);
			return false;
		}
		else
			CCLOG("The hostname resolved successfully!\n");

		CopyMemory(&server.sin_addr, host->h_addr_list[0], host->h_length);
		
	}
	// Non-Blocking
	u_long iMode = 1;
	ioctlsocket(sClient, FIONBIO, &iMode);
	
	return true;
}

bool Client::connectClient()
{
	if (connect(sClient, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		CCLOG("connect() failed with error code %d\n", WSAGetLastError());
	}
	else
		CCLOG("connect() is pretty damn fine!\n");
	
	return true;
}

bool Client::sendData()
{
	
	ret = send(sClient, _packet, _size, 0);
	if (ret == 0)
		return false;
	else if (ret == SOCKET_ERROR)
	{
		//CCLOG("send() failed with error code %d\n", WSAGetLastError());
		return false;
	}

	//CCLOG("send() should be fine. Send %d bytes\n", ret);
	return true;
}

bool Client::recvData()
{
	ret = recv(sClient, szBuffer, DEFAULT_BUFFER, 0);
	if (ret == 0)        // Graceful close
	{
		//CCLOG("It is a graceful close!\n");
		return false;
	}
	else if (ret == SOCKET_ERROR)
	{
		//CCLOG("recv() failed with error code %d\n", WSAGetLastError());
		return false;
	}
	szBuffer[ret] = '\0';
	CCLOG("recv() is OK. Received %d bytes: %s\n", ret, szBuffer);
	if (LPTail + ret > BUFFER_SIZE)
	{
		LPTail = 0;
	}
	else
	{
		memcpy(Buffer + LPTail, szBuffer, ret);
		LPTail += ret;
	}
	return true;
}

bool Client::closeClient()
{
	if (closesocket(sClient) == 0)
	{
		CCLOG("closesocket() is OK!\n");
		return true;
	}
	else
		CCLOG("closesocket() failed with error code %d\n", WSAGetLastError());
	return false;
}

bool Client::cleanUpClient()
{
	if (WSACleanup() == 0)
	{
		CCLOG("WSACleanup() is fine!\n");
		return true;
	}
	else
		CCLOG("WSACleanup() failed with error code %d\n", WSAGetLastError());
	return false;
}

void Client::Reset()
{
	LPHead = 0;
	LPTail = 0;
}

int Client::getTeam()
{
	int Team;
	memcpy(&Team, szBuffer, sizeof(int));
	if (Team != 0)
		return Team;
	return 0;
}

void Client::PacketSend(TANK_STATE player)
{	
	_size = sizeof TANK_STATE;
	_packet = new char[_size];
	memcpy(_packet, &player, sizeof TANK_STATE);
}

int Client::Extras(UPDATE_WORLD world)
{
	int teamWin = 0;
	int sizePlayer, sizeBrick, sizeBullet;
	if (LPHead > LPTail)
	{
		LPHead = 0;

	}
	else
	{
		memcpy(&teamWin, szBuffer + LPHead, sizeof(int));
		memcpy(&sizePlayer, szBuffer + LPHead + sizeof(int), sizeof(int));
		memcpy(&sizeBrick, szBuffer + LPHead + 2 * sizeof(int), sizeof(int));
		memcpy(&sizeBullet, szBuffer + LPHead + 3 * sizeof(int), sizeof(int));
		int sizeOfServer = sizePlayer * sizeof TANK_STATE + sizeBrick * sizeof BRICK + 4 * sizeof(int) + sizeBullet * sizeof BULLET_STATE;
		for (int i = 0; i < sizePlayer; i++)
		{
			TANK_STATE playertemp;
			memcpy(&playertemp, szBuffer + LPHead + 4 * sizeof(int) + i * sizeof TANK_STATE, sizeof TANK_STATE);
			world.allPlayer[i]->Move = playertemp.Move;
			world.allPlayer[i]->PosX = playertemp.PosX;
			world.allPlayer[i]->PosY = playertemp.PosY;
			world.allPlayer[i]->Shooting = playertemp.Shooting;
			world.allPlayer[i]->SideShoot = playertemp.SideShoot;
			world.allPlayer[i]->Tank = playertemp.Tank;
			world.allPlayer[i]->isDie = playertemp.isDie;
			//CCLOG("%f %f", playertemp.PosX, playertemp.PosY);
		}

		//char *temp2 = szBuffer + 3 * sizeof(int) + sizePlayer * sizeof(PLAYER_STATE);
		for (int i = 0; i < sizeBrick; i++)
		{
			BRICK brick;
			memcpy(&brick, szBuffer + LPHead + 4 * sizeof(int) + sizePlayer * sizeof TANK_STATE + i * sizeof BRICK, sizeof BRICK);
			world.allBrick[brick.ID]->ID = brick.ID;
			world.allBrick[brick.ID]->isDie = brick.isDie;
			world.allBrick[brick.ID]->PosX = brick.PosX;
			world.allBrick[brick.ID]->PosY = brick.PosY;
			//CCLOG("%f %f", world.allBrick[i]->PosX, world.allBrick[i]->PosY);
		}
		for (int i = 0; i < sizeBullet; i++)
		{
			BULLET_STATE bullet;
			memcpy(&bullet, szBuffer + LPHead + 4 * sizeof(int) + sizePlayer * sizeof TANK_STATE + sizeBrick * sizeof BRICK + i * sizeof BULLET_STATE, sizeof BULLET_STATE);
			world.allBullet[bullet.ID]->IsVisible = bullet.IsVisible;
			world.allBullet[bullet.ID]->Move = bullet.Move;
			world.allBullet[bullet.ID]->Own = bullet.Own;
			world.allBullet[bullet.ID]->PosX = bullet.PosX;
			world.allBullet[bullet.ID]->PosY = bullet.PosY;
		}
		//LPHead += sizeOfServer;
	}
	return teamWin;
}
