
#define _CRT_SECURE_NO_WARNINGS
#include "GlobalFunction.h"


int main(int argc, char **argv)
{
	InitializeCriticalSection(&criticalDataRecv);

	//Empty data
	for (int i = 0; i < 4; i++)
	{
		dataRecv[i] = new DataGame();
	}
	networkProc = (HANDLE)_beginthread(&NetworkProc, 0, 0);
	//dataProc = (HANDLE)_beginthread(&DataProc, 0, 0);
	gameProc = (HANDLE)_beginthread(&GameProc, 0, 0);
	WaitForSingleObject(gameProc, INFINITE);
	for (int i = 0; i < numOfPlayer; i++)
	{
		closesocket(socketArray[i]->socket);
		printf("Closing socket number %d\n", socketArray[i]->socket);
		GlobalFree(socketArray[i]);
	}
	gameEnded = true;
	DeleteCriticalSection(&criticalDataRecv);
	return 1;
}