#include "Programmer.h"
#include <stdio.h>


int main(int argc, char * argv[])
{
	int x;
	HANDLE hComm;    
	DWORD CMS;
	int oscal[READ_DATA_LENGTH];
	
	int command[]={1,0,0,1,1,1,1,1,1,1,1,1,1,1};
	
	int delka;
	delka=5;
	int pole[5]={0,0,1,0,0};
	pole[0]=7;
	
	printf("Vitejte v programu pro cteni OSCAL z PIC16F630 s pouzitim naseho genialniho PROGRAMATORU Vasek1.\n");
	hComm = CreateFile("COM4",GENERIC_WRITE,0,0,OPEN_EXISTING, FILE_FLAG_OVERLAPPED,0);
	setZeros(hComm);

	programVerifyMode(hComm);
	printf("Now entered Program/Verify mode...\n");
//	incrementAddress(hComm, 1023);
	incrementAddress(hComm, 10);

	readDataFromProgramMemory(hComm, oscal, READ_DATA_LENGTH);
	   
    
//    loadDataToProgramMemory(hComm, command);
//    beginProgramingInternal(hComm);
    
    setZeros(hComm);
	CloseHandle(hComm);

    
    
    //printf("\n");
    printf("Prectena hodnota OSCAL: ");
    //for (int i = 0; i < READ_DATA_LENGTH; i++)
    for (int i = 0; i <READ_DATA_LENGTH; i++)
	{
        	printf("%d", oscal[i]);
    }
	
	
	printf("\n");
	printf("Pro ukonceni programu napiste cislo a stiskene ENTER...\n");
	scanf("%i", &x);
	return 0;
}
