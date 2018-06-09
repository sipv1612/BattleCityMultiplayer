#include "Client.h"
#include "GlobalVariable.h"
#include "TankMgr.h"
#include "BulletManager.h"
#include "TerrainManager.h"

Client* Client::instance = 0;

Client::Client()
{
	initClient();
	connectClient();
}

Client * Client::GetInstance()
{
	if (!instance)
		instance = new Client();
	return instance;
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
	memcpy(dataSendBuffer, &LPDataSendBuffer, sizeof(int));
	ret = send(sClient, dataSendBuffer, LPDataSendBuffer, 0);
	if (ret == 0)
		return false;
	else if (ret == SOCKET_ERROR)
	{
		//CCLOG("send() failed with error code %d\n", WSAGetLastError());
		return false;
	}

	//CCLOG("send() should be fine. Send %d bytes\n", ret);
	LPDataSendBuffer = sizeof(int);
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
	//CCLOG("recv() is OK. Received %d bytes: %s\n", ret, szBuffer);
	
	/*memcpy(&dataSize, szBuffer, sizeof(int));
	dataSize -= sizeof(int);*/
	//CCLOG("%d \n", dataSize);
	if (LPTail + ret > BUFFER_SIZE)
	{
		LPTail = 0;
	}
	memcpy(Buffer + LPTail, szBuffer, ret);
	LPTail += ret;

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



int Client::Extras()
{
	//int teamWin = 0;
	//int sizePlayer, sizeBrick, sizeBullet;

	if (LPHead + ret > BUFFER_SIZE)
	{
		LPHead = 0;

	}

	if (LPHead < LPTail)
	{
		memcpy(&dataSize, Buffer + LPHead, sizeof(int));
		int packetLimitPerFrame = LPHead + dataSize;
		LPHead += sizeof(int);

		while (LPHead < packetLimitPerFrame)
		{

			PACKET_KEY key = PACKET_KEY(Nothing);
			memcpy(&key, Buffer + LPHead, sizeof PACKET_KEY);
			LPHead += sizeof PACKET_KEY;
			int keySize = 0;
			TANK_MOVE tankMove;
			TANK_DIE tankDie;
			TANK_REVIVAL tankRivival;
			BULLET_SPAWN bulletSpawn;
			BULLET_DIE bulletDie;
			TERRAIN_DIE terrainDie;

			switch (key.key)
			{
			case TankMove:
				keySize = sizeof TANK_MOVE;
				memcpy(&tankMove, Buffer + LPHead, keySize);
				LPHead += keySize;
				TankMgr::GetInstance()->HandleMovePackage(tankMove);

				CCLOG("TankMove %f %f", tankMove.posX, tankMove.posY);
				break;

			case TankDie:
				keySize = sizeof TANK_DIE;
				memcpy(&tankDie, Buffer + LPHead, keySize);
				LPHead += keySize;
				TankMgr::GetInstance()->HandleDiePackage(tankDie);
				CCLOG("TankDie %d", tankDie.idTank);

				break;

			case TankRevial:
				keySize = sizeof TANK_REVIVAL;
				memcpy(&tankRivival, Buffer + LPHead, keySize);
				LPHead += keySize;
				TankMgr::GetInstance()->HandleRevivalPackage(tankRivival);

				CCLOG("TankRevial %f %f", tankRivival.posX, tankRivival.posY);

				break;

			case BulletSpawn:
				keySize = sizeof BULLET_SPAWN;
				memcpy(&bulletSpawn, Buffer + LPHead, keySize);
				LPHead += keySize;
				CCLOG("BulletSpawn %f %f", bulletSpawn.posX, bulletSpawn.posY);

				break;

			case BulletDie:
				keySize = sizeof BULLET_DIE;
				memcpy(&bulletDie, Buffer + LPHead, keySize);
				LPHead += keySize;
				CCLOG("BulletDie %d", bulletDie.idBullet);

				break;

			case TerrainDie:
				keySize = sizeof TERRAIN_DIE;
				memcpy(&terrainDie, Buffer + LPHead, keySize);
				LPHead += keySize;
				CCLOG("TerrainDie %d", terrainDie.idTerrain);

				break;

			default:
				break;
			}
		}

	}

	dataSize = 0;
	return 0;
}
