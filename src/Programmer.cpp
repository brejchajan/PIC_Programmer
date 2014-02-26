#include "Programmer.h"
#include <stdio.h>

void incrementAddress(HANDLE hComm, int offset)
{
	int incCommand[6] = {0, 1, 1, 0, 0, 0};
	int velikost_pole;
	int i;
    velikost_pole=(sizeof(incCommand) / sizeof(int));
	for (i = 0; i < offset; i++)
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
	Sleep(1); //oddelemi mezi prikazem a prijmem dat
	
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


void loadDataToProgramMemory(HANDLE hComm,int *command)
{
	//int loadDataCommand[] = {0, 0, 0, 0, 0, 0};
	int loadDataCommand[] = {0, 1, 0, 0, 0, 0};
	int velikost_prikazu;
    velikost_prikazu=(sizeof(loadDataCommand) / sizeof(int));
    int size_of_load=velikost_prikazu+COMMAND_LENGTH+2;
    int * loadCommand = (int *)calloc(size_of_load, sizeof(int));
    int j=0; 
    int i;
   for (i = (size_of_load-2); i > (velikost_prikazu-2) ; i--)
   {
        	loadCommand[i]=command[j];
        	j=j+1;
            
            //printf("%d", command[i]);
    } 
   for (i = 0; i <velikost_prikazu ; i++)
	{
        loadCommand[i]=loadDataCommand[i];	
    }
    
    //start+stop bit
    loadCommand[velikost_prikazu]=0;
    loadCommand[size_of_load-1]=0;
    
//    for (int i = 0; i <size_of_load ; i++)
//	{
//        	printf("%d", loadCommand[i]);
//    }
    setData(hComm, loadCommand, size_of_load);
}


void beginProgramingInternal(HANDLE hComm)
{
	int beginProgramingCommand[6] = {0, 0, 0, 1, 0, 0};
	int velikost_pole;
    velikost_pole=(sizeof(beginProgramingCommand) / sizeof(int));
	
    setData(hComm, beginProgramingCommand, velikost_pole);
	Sleep(2);

}




void loadConfigurationData(HANDLE hComm,int *command)
{
	int loadDataCommand[] = {0, 0, 0, 0, 0, 0};
	int velikost_prikazu;
    velikost_prikazu=(sizeof(loadDataCommand) / sizeof(int));
    int size_of_load=velikost_prikazu+COMMAND_LENGTH+2;
    int * loadCommand = (int *)calloc(size_of_load, sizeof(int));
    int j=0; 
    int i;
   for (i = (size_of_load-2); i > (velikost_prikazu-2) ; i--)
   {
        	loadCommand[i]=command[j];
        	j=j+1;
            
            //printf("%d", command[i]);
    } 
   for (i = 0; i <velikost_prikazu ; i++)
	{
        loadCommand[i]=loadDataCommand[i];	
    }
    
    //start+stop bit
    loadCommand[velikost_prikazu]=0;
    loadCommand[size_of_load-1]=0;
    
//    for (int i = 0; i <size_of_load ; i++)
//	{
//        	printf("%d", loadCommand[i]);
//    }
    setData(hComm, loadCommand, size_of_load);
}



void bulkEraseProgramMemory(HANDLE hComm)
{
	int  bulkEraseProgramMemoryCommand[6] = {1, 0, 0, 1, 0, 0};
	int velikost_pole;
    velikost_pole=(sizeof(bulkEraseProgramMemoryCommand) / sizeof(int));
	
    setData(hComm, bulkEraseProgramMemoryCommand, velikost_pole);
	Sleep(2);

}


void programVerifyMode(HANDLE hComm)
{
	EscapeCommFunction(hComm, SETDTR);
	//Sleep for 2 seconds
	Sleep(2000);
}
