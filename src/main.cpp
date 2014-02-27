#include "Programmer.h"
#include <stdio.h>
#include <stdlib.h>

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
    int oscal_write[READ_DATA_LENGTH];
	int configWord[READ_DATA_LENGTH];
	int write_data[READ_DATA_LENGTH]; //precteni zapsanych dat
	
	long command[]={1,0,0,1,1,1,1,1,1,1,1,1,1,1}; //prikaz, ktery bude zapsan do pameti
	int command2[COMMAND_LENGTH];
	int config[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //konfiguracni slovo pri loadConfigurationData ?? nema vyznam
	
	int delka;
	delka=5;
	int pole[5]={0,0,1,0,0};
	pole[0]=7;
	
	
	FILE *soubor;
    char nacitani_souboru[1];
    char cesta_souboru[50];
    int detekce_chyby;  
    char *chyba;
    int cislo_instrukce;
    int configuration[COMMAND_LENGTH]; //nastaveni konfigurace
	
	printf("Vitejte v programu pro cteni OSCAL z PIC16F630 s pouzitim naseho genialniho PROGRAMATORU Vasek1.\n");
	hComm = CreateFile("COM4",GENERIC_WRITE,0,0,OPEN_EXISTING, FILE_FLAG_OVERLAPPED,0);
	setZeros(hComm);

	programVerifyMode(hComm);
	printf("Now entered Program/Verify mode...\n");
	//read OSCAL
	
    incrementAddress(hComm, 1023);
	
    readDataFromProgramMemory(hComm, oscal, READ_DATA_LENGTH);
    
    printf("Prectena hodnota OSCAL: ");
    printData(oscal);
    

    	//read CONFIG WORD
    	
        loadConfigurationData(hComm, config);
     	incrementAddress(hComm, 7);
    	readDataFromProgramMemory(hComm, configWord, READ_DATA_LENGTH);

    	
        printf("Prectena hodnota CONFIGWORD: ");
        printData(configWord);

        
        //Opusteni konfiguracni pamenti a vraceni do pameti programu
        printf("\nOpusteni konfiguracni pamenti a vraceni do pameti programu...\n");
        setZeros(hComm);
	    programVerifyMode(hComm);
	    
	    
	    //Vymazani programove pameti
	    bulkEraseProgramMemory(hComm);
	    printf("\nVymazani programove pamenti a vraceni do pameti programu...\n");
	    setZeros(hComm);
	    programVerifyMode(hComm);
	    
       
// Nacitani prikazu ze souboru a zapis do programove pameti
        detekce_chyby=0;
        cislo_instrukce=0;
        printf("\n\nZadejte cestu k souboru o delce 50 znaku a ve tvaru: C:\\vasek\\Eoe\\cecko\\soubor.txt\n");   //C:\vasek\Eoe\cecko\data.txt
        scanf("%s",&cesta_souboru); 
        
        if ((soubor=fopen(cesta_souboru,"r"))==NULL)
           {printf("Soubor se nepodarilo otevrit!\n");}
        else
        {
             printf("Cisla souboru\n\n");
              while (1==1)
                 {  
                     //detekce chyby v prevodu char na cislo
                     detekce_chyby=0;
                     for(i=0; i<COMMAND_LENGTH; i++)
                     {
                         nacitani_souboru[0] = fgetc(soubor);
                         //ukonceni cyklu na konci programu
                         if(nacitani_souboru[0]==EOF)
                              {break;}
                        //prevod textoveho cisla na int 
                         command[i] = strtol(nacitani_souboru, &chyba, 10);
                         if (*chyba == nacitani_souboru[0])
                          {
                            detekce_chyby=1;
                            break;
                           }
                         else //kontrola na 0 a 1
                        {
                         if ((command[i]==0)||(command[i]==1))
                          {}
                         else 
                          {
                            detekce_chyby=2;
                            printf("Instrukce programu ve spatnem formatu!\n\n");
                            break;
                           }
                        }   
                     }
             
                     //preskoceni textovych poznamek
                     if(nacitani_souboru[0]!='\n')
                           {
                             do {
                                  nacitani_souboru[0]= fgetc(soubor);
                                  //ukonceni cyklu na konci programu
                                  if(nacitani_souboru[0]==EOF)
                                      {break;}
                               } while (nacitani_souboru[0] != '\n');
                           }
                     //ukonceni cyklu na konci programu
                     if(nacitani_souboru[0]==EOF)
                           {break;}
                     
                    if((detekce_chyby!=1)&&(detekce_chyby!=2))
                           {
                              
                                        //printf("%i",command[i]);
                                        for (i = 0; i < READ_DATA_LENGTH; i++)
                                            {command2[i] = (int)command[i];}
                                        
                                        if(cislo_instrukce==0)
                                            {
                                               for( i=0; i<COMMAND_LENGTH; i++)
                                                 {
                                                   configuration[i]=command[i];
                                                 }
                                                //printf("configurace");
                                            }
                                        else
                                            {
                                                //zapis command do pameti                                            
                                                loadDataToProgramMemory(hComm, command2);
                                                beginProgramingInternal(hComm);
                                                
                                                //Kontrola zapisu dat
                                                readDataFromProgramMemory(hComm, write_data, READ_DATA_LENGTH);
                                                for (int i = 0; i < READ_DATA_LENGTH; i++)
                                                	{
                                                        if(command[i]!=write_data[READ_DATA_LENGTH-i-1])
                                                            {
                                                                detekce_chyby=2;
                                                                break;
                                                            }
                                                        
                                                    }
                                                 
                                                printData(write_data);       
                                            }
                                        cislo_instrukce=cislo_instrukce+1;
                                        incrementAddress(hComm, 1);
                                   
                           
                           
                              //printf("\n");
                           }            
    
                     if(detekce_chyby==2)
                         {
                           printf("Nastala chyba zapisu dat do programove pameti!\n");
                           break;
                         } 
                 }
            fclose(soubor);
          
        }

    
    
    
//Zapis hodnoty Oscal______________________________________________________________________    
     printf("\nZapis hodnoty Oscal...\n");       
     setZeros(hComm);
     programVerifyMode(hComm);         
     
         for( i=0; i<COMMAND_LENGTH; i++)
         {
             oscal_write[i]=oscal[COMMAND_LENGTH-i-1];
         }
         
         incrementAddress(hComm, 1023);
         loadDataToProgramMemory(hComm, oscal_write);
         beginProgramingInternal(hComm);
         
       
         readDataFromProgramMemory(hComm, oscal, READ_DATA_LENGTH);
         for (int i = 0; i < READ_DATA_LENGTH; i++)
       	{
            if(oscal[i]!=oscal_write[READ_DATA_LENGTH-i-1])
                {
                   printf("Spatne zapsane oscal! \n");
                   break;
                }

        }
         
         
         
         printf("Hodnota Oscal: \n"); 
         printData(oscal);
         

// Configurace______________________________________________________         
         for( i=0; i<CONFIG_BITS; i++)
         {
              configuration[i]=configWord[COMMAND_LENGTH-i-1];
         }
        
    	
        loadConfigurationData(hComm, config);
     	incrementAddress(hComm, 7);
        loadDataToProgramMemory(hComm, configuration);
        beginProgramingInternal(hComm);

        
        
        readDataFromProgramMemory(hComm, configWord, READ_DATA_LENGTH);
        for (int i = 0; i < READ_DATA_LENGTH; i++)
       	{
            if(configWord[i]!=configuration[READ_DATA_LENGTH-i-1])
                {
                   printf("Spatne zapsane konfiguracni slovo! \n");
                   break;
                }

        }

        printf("Hodnota Configurace: \n");
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
