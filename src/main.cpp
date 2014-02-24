#include "Programmer.h"
#include <stdio.h>

void printData(int * data)
{
	for (int i = 0; i < READ_DATA_LENGTH; i++)
	{
        printf("%d", data[i]);
    }
	printf("\n");
}


int main(int argc, char * argv[])
{
    int i;
	int x;
	HANDLE hComm;    
	DWORD CMS;
	int oscal[READ_DATA_LENGTH];
	int configWord[READ_DATA_LENGTH];
	
	int command[]={1,0,0,1,1,1,1,1,1,1,1,1,1,1}; //prikaz, ktery bude zapsan do pameti
	int config[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //konfiguracni slovo pri loadConfigurationData ?? nema vyznam
	
	int delka;
	delka=5;
	int pole[5]={0,0,1,0,0};
	pole[0]=7;
	
	printf("Vitejte v programu pro cteni OSCAL z PIC16F630 s pouzitim naseho genialniho PROGRAMATORU Vasek1.\n");
	hComm = CreateFile("COM4",GENERIC_WRITE,0,0,OPEN_EXISTING, FILE_FLAG_OVERLAPPED,0);
	setZeros(hComm);

	programVerifyMode(hComm);
	printf("Now entered Program/Verify mode...\n");
	//read OSCAL
	
    //incrementAddress(hComm, 1023);
	
    //readDataFromProgramMemory(hComm, oscal, READ_DATA_LENGTH);
    
    //printf("Prectena hodnota OSCAL: ");
    //printData(oscal);
    

    	//read CONFIG WORD
    	
        loadConfigurationData(hComm, config);
     	incrementAddress(hComm, 7);
    	readDataFromProgramMemory(hComm, configWord, READ_DATA_LENGTH);

    	
        printf("Prectena hodnota CONFIGWORD: ");
        printData(configWord);

//    loadDataToProgramMemory(hComm, command);
//    beginProgramingInternal(hComm);

    setZeros(hComm);
	CloseHandle(hComm);
	
	printf("\n");
	printf("Pro ukonceni programu napiste cislo a stiskene ENTER...\n");
	scanf("%i", &x);
	return 0;
}
