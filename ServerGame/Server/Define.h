#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <vector>


#define DEFAULT_PORT 5150
#define DATA_BUFSIZE 8192
#define CMD_BUFSIZE 102400
#define NUM_OF_PLAYER 2
#define BYTE_OF_CLIENT 28
#define FRAME_PER_SEC 120

#pragma region GameInfo
#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 704

#define TANK_SPEED 100.0f
#define TANK_SIZE 28
#define TANK_TIME_TO_RESURRECTION 3
#define TANK_SHOOT_RATE 3

#define ROBOT_SPEED 70.0f
#define ROBOT_SHOOT_RATE 3
#define ROBOT_TIME_AI 3
#define BULLET_WIDTH 2.8125
#define BULLET_HEIGHT 3.75
#define BULLET_SPEED 200.0f

#define TERRIAN_SIZE 32

#define MAP_WIDTH 25
#define MAP_HEIGHT 23
#define MAP_TILED_SIZE 32
#define MAP_TERRAIN_RED 1
#define MAP_TERRAIN_SLIVER 3
#define MAP_TANK_TEAM_1 5
#define MAP_TANK_TEAM_2 4
#define MAP_BIRTH_TEAM_1 6
#define MAP_BIRTH_TEAM_2 2


#pragma endregion GameInfo

