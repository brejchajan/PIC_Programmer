#include "Programmer.h"

int main(int argc, char * argv[])
{
	HANDLE hComm;    
	DWORD CMS;
	int x;
	int oscal[READ_DATA_LENGTH];
	printf("Vitejte v programu pro cteni OSCAL z PIC16F630 s pouzitim naseho genialniho PROGRAMATORU Vasek1.\n");
	hComm = CreateFile("COM4",GENERIC_WRITE,0,0,OPEN_EXISTING, FILE_FLAG_OVERLAPPED,0);
	setZeros(hComm);

	programVerifyMode(hComm);
	printf("Now entered Program/Verify mode...\n");
	incrementAddress(hComm, 1023);

	readDataFromProgramMemory(hComm, oscal, READ_DATA_LENGTH);
	setZeros(hComm);
	CloseHandle(hComm);

	printf("Prectena hodnota OSCAL: ");
	for (int i = 0; i < READ_DATA_LENGTH; i++)
		printf("%d", oscal[i]);
	printf("\n");
	printf("Pro ukonceni programu napiste cislo a stiskene ENTER...\n");
	scanf("%i", &x);
	return 0;
}
