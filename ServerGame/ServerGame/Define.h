#pragma once

#include <iostream>
#include <vector>
#include <WinSock2.h>
#include <process.h>

#define DEFAULT_PORT 5150
#define DATA_BUFSIZE 8192
#define CMD_BUFSIZE 102400
#define NUM_OF_PLAYER 2
#define BYTE_OF_CLIENT 28

#pragma region GameInfo
#define TANK_SPEED 100.0f
#define ROBOT_SPEED 70.0f
#define SPEED_BULLET 200.0f
#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 704
#define TANK_SIZE 28
#define BULLET_WIDTH 2.8125
#define BULLET_HEIGHT 3.75
#define TERRIAN_SIZE 32

#pragma endregion GameInfo


class Box {
public:
	float x, y, vx, vy;
	float width, height;

	Box() {
		x = y = vx = vy = width = height = 0;
	}

	Box(float x, float y, float vx, float vy, int width, int height)
	{
		this->x = x;
		this->y = y;
		this->vx = vx;
		this->vy = vy;
		this->width = width;
		this->height = height;
	}
};
class DataGame
{
private:
	char* data;
	int LPTail;
	
public:
	DataGame()
	{
		data = new char[CMD_BUFSIZE];
		LPTail = 0;
		
	}

	char* GetData()
	{
		return data;
	}

	void Add(char* value, int size)
	{
		if (size + LPTail > CMD_BUFSIZE)
		{
			LPTail = 0;
		}
		memcpy(data + LPTail, value, size);
		LPTail += size;
	}
	int GetIndex()
	{
		return LPTail;
	}

};
class DataSrc {
public:
	static CRITICAL_SECTION criticalDataRecv;
	static bool gameRunning;
	static bool gameEnded; // true when the application off
	static DataGame** dataRecv;
	static int numOfPlayer;
	
};

typedef struct _SOCKET_INFORMATION {
	CHAR buffer[DATA_BUFSIZE];
	WSABUF dataBuf;
	WSABUF dataBufSend;
	SOCKET socket;
	OVERLAPPED Overlapped;
	DWORD bytesSEND;
	DWORD bytesRECV;
} SOCKET_INFORMATION, *LPSOCKET_INFORMATION;
enum eMove
{
	NONE = 0,
	UP = 1,
	LEFT = 2,
	RIGHT = 3,
	DOWN = 4,
	DIE
};

enum Owned {
	TEAM_1,
	TEAM_2
};
enum TerrianType { REB, SILVER };

typedef struct
{
	Owned Tank;
	eMove Move;
	bool Shooting;
	eMove SideShoot;
	float PosX;
	float PosY;
	bool isDie;
}TANK_STATE;

typedef struct
{
	int priority;
}Priority;
typedef struct
{
	bool isVisible;
	float PosX;
	float PosY;
	eMove Move;
	Owned Own;
}BULLET_STATE;

typedef struct
{
	int ID;
	bool isDie;
	float PosX;
	float PosY;
}BRICK_WORLD;
typedef struct
{
	int teamWin;
	std::vector<BULLET_STATE*> allBullet;
	std::vector<TANK_STATE*> allTank;
	std::vector<BRICK_WORLD*> allBrick;
}UPDATE_WORLD;
