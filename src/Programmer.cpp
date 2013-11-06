#include "Programmer.h"
#include <stdio.h>

void incrementAddress(HANDLE hComm, int offset)
{
	int incCommand[6] = {0, 1, 1, 0, 0, 0};
	int velikost_pole;
    velikost_pole=(sizeof(incCommand) / sizeof(int));
	for (int i = 0; i < offset; i++)
	{	
		setData(hComm, incCommand, velikost_pole);
		//Sleep(1);
	}
}

void readDataFromProgramMemory(HANDLE hComm, int *buffer, int size)
{
	int readDataCommand[] = {0, 0, 1, 0, 0, 0};
	int velikost_pole;
    velikost_pole=(sizeof(readDataCommand) / sizeof(int));
	setData(hComm, readDataCommand, velikost_pole);
	//Sleep(1);
	setClock1(hComm);
	//Sleep(1);
	setClock0(hComm);
	//Sleep(1);
	//printf("cteni dat\n");
	//scanf("%i",&x);
	readData(hComm, buffer, size);
	setClock1(hComm);
	//Sleep(1);
	setClock0(hComm);
	//Sleep(1);
}

void programVerifyMode(HANDLE hComm)
{
	EscapeCommFunction(hComm, SETDTR);
	//Sleep for 20 seconds
	Sleep(20000);
}
