#pragma once
#include "DataGame.h"
#include "Define.h"
#include "GlobalStruck.h"

extern bool gameRunning;
extern bool gameEnded;
extern int numOfPlayer;
extern char* dataSendBuffer;
extern int LPDataSendBuffer;
extern HANDLE networkProc;
extern HANDLE gameProc;
extern DWORD Total;
extern FD_SET WriteSet;
extern FD_SET ReadSet;
extern LPSOCKET_INFORMATION socketArray[FD_SETSIZE];
extern DataGame** dataRecv;
extern CRITICAL_SECTION criticalDataRecv;