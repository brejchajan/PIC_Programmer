#include "basicBusCommands.h"
#include <stdio.h>

void setDataWrite0(HANDLE hComm)
{
	EscapeCommFunction(hComm,CLRRTS);
}

void setDataWrite1(HANDLE hComm)
{
	EscapeCommFunction(hComm,SETRTS);
}

int dataRead(HANDLE hComm)
{
	DWORD CMS;
	GetCommModemStatus(hComm, &CMS);
	if(CMS & MS_CTS_ON)
		return 1;
	return 0;
}

void setClock0(HANDLE hComm)
{
	//TXD = BREAK - GO TO HELL FUCKING WINDOWS!!!
	EscapeCommFunction(hComm, CLRBREAK);
}

void setClock1(HANDLE hComm)
{
	//TXD = BREAK - GO TO HELL FUCKING WINDOWS!!!
	EscapeCommFunction(hComm, SETBREAK);
}


void setZeros(HANDLE hComm)
{
	EscapeCommFunction(hComm,CLRDTR);
	EscapeCommFunction(hComm,CLRRTS);
	EscapeCommFunction(hComm,CLRBREAK);
	Sleep(1);
}



void setData(HANDLE hComm, int data[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		setDataChunk(hComm, data[i]);
	}
}

void setDataChunk(HANDLE hComm, int data)
{
    setClock0(hComm);
	//Sleep(1);
	if (data == 0)
	{
		setDataWrite0(hComm);
	}
	else
    {
        setDataWrite1(hComm);
    }
	//Sleep(1);
	setClock1(hComm);
	//Sleep(1);
	setClock0(hComm);
	//Sleep(1);
}

int readDataChunk(HANDLE hComm)
{
	int res = 0;
	setClock0(hComm);
	Sleep(1);
	setClock1(hComm);
	res = dataRead(hComm);
	Sleep(1);
	setClock0(hComm);
	return res;
}

void readData(HANDLE hComm, int *buffer, int size)
{
	for (int i = 0; i < size; i++)
	{
		buffer[i] = readDataChunk(hComm);
	}
}
