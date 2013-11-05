#include "Programmer.h"


void incrementAddress(HANDLE hComm, int offset)
{
	int incCommand[] = {0, 1, 1, 0, 0, 0};
	for (int i = 0; i < offset; i++)
	{	
		setData(hComm, incCommand);
		Sleep(1);
	}
}

void readDataFromProgramMemory(HANDLE hComm, int *buffer, int size)
{
	int readDataCommand[] = {0, 0, 1, 0, 0, 0};
	setData(hComm, readDataCommand);
	Sleep(1);
	setClock1(hComm);
	Sleep(1);
	setClock0(hComm);
	Sleep(1);
	readData(hComm, buffer, size);
	setClock1(hComm);
	Sleep(1);
	setClock0(hComm);
	Sleep(1);
}

void programVerifyMode(HANDLE hComm)
{
	EscapeCommFunction(hComm, SETDTR);
	//Sleep for 20 seconds
	Sleep(20000);
}