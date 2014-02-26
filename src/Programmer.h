#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include "basicBusCommands.h"
#include <cstdio>
#include <windows.h>

#define READ_DATA_LENGTH 14
#define COMMAND_LENGTH 14
#define CONFIG_BITS 5  //bity konfigurace, ktere se musi zachovat

/**
	I/O SETUP

	Data		- CTS = READ from PIC
				- RTS = WRITE to PIC
	Clock		- TXD (called BREAK)
	Vdd, MCLR	- DTR
*/

/**
	Increments address of the PC.
	Must be in Program/Verify mode
	@param [in] hComm	handle to the COM port.
	@param [in] count	offset in the memory
*/
void incrementAddress(HANDLE hComm, int offset);

void readDataFromProgramMemory(HANDLE hComm, int *buffer, int size);

void loadDataToProgramMemory(HANDLE hComm,int *command);

void beginProgramingInternal(HANDLE hComm);

void loadConfigurationData(HANDLE hComm,int *command);

void bulkEraseProgramMemory(HANDLE hComm);

/**
	Enters Program/Verify mode
	Waits for at least 2 seconds to do the synchronization with
	programmer properly.
	@param [in] hComm	handle to the COM port.
*/
void programVerifyMode(HANDLE hComm);


#endif
