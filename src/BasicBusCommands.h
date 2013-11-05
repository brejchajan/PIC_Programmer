#ifndef BASIC_BUS_COMMANDS_H
#define BASIC_BUS_COMMANDS_H

#include <windows.h>
#include <winbase.h>


/**
	Sets all inputs to the PIC to zeros.
	@param [in] hComm	handle to the COM port.
*/
void setZeros(HANDLE hComm);


void setData(HANDLE hComm, int data[], int size);

void setDataChunk(HANDLE hComm, int data);

void setDataWrite0(HANDLE hComm);

void setDataWrite1(HANDLE hComm);

int dataRead(HANDLE hComm);

void setClock0(HANDLE hComm);

void setClock1(HANDLE hComm);

int readDataChunk(HANDLE hComm);

/**
	Reads data from PIC of buffer size
	@param [in] hComm		handle to COM port
	@param [in, out] buffer	pointer to data array
*/
void readData(HANDLE hComm, int *buffer, int size);

#endif //BASIC_BUS_COMMANDS
