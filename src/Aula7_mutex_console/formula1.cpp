#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <conio.h>


// nomeamos ponteiro para uma função que retorna unsigned int e recebe um LPVOID como CAST_FUNCTION
// WINAPI expande para ;__stdcall, e diz respeito a uma convenção de chamada de funções, é relevante para interações com o SO
typedef unsigned (WINAPI *CAST_FUNCTION)(LPVOID); 
typedef unsigned *CAST_LPDWORD; // nomeamos o tipo unsigned int * como CAST_LPDWORD

#define EQUIPES 7
#define MAX_CARROS_PISTA 5
#define NUM_CARROS 10
HANDLE hMutex[EQUIPES];
HANDLE hSemaphore;

//Declaração da função,DWORD expande para unsigned long
DWORD WINAPI FuncCar(LPVOID);

int main(){
    HANDLE hThreads[NUM_CARROS];
    DWORD dwThreadId;
    DWORD dwExitCode = 0;
    DWORD dwRet;
    int nEquipe, nCar;
    char BoxName[5];

    for(nEquipe=0; nEquipe<EQUIPES;nEquipe++){
        sprintf(BoxName, "Box %d",nEquipe);
        hMutex[nEquipe] = CreateMutex(NULL,FALSE,BoxName);
    }
    //Cria um semáforo com contagem máxima MAX_CARROS_PISTA e o inicializa com o valor MAX_CARROS_PISTA.
    hSemaphore = CreateSemaphore(NULL,MAX_CARROS_PISTA,MAX_CARROS_PISTA,"MAX_CARROS");

    for(nCar = 0;nCar<NUM_CARROS;nCar++){
        nEquipe = rand()%EQUIPES;
        hThreads[nCar] = (HANDLE) _beginthreadex(NULL,0,(CAST_FUNCTION)FuncCar,(LPVOID)((nCar<<8)+nEquipe),0,(CAST_LPDWORD)&dwThreadId);
        if(hThreads[nCar])
            printf("Carro %2d - Scuderia %d - ID: %0x \n",nCar, nEquipe, dwThreadId);
    }

    dwRet = WaitForMultipleObjects(NUM_CARROS,hThreads,TRUE,INFINITE);
    for(nCar = 0;nCar,NUM_CARROS; nCar++){
        dwRet = GetExitCodeThread(hThreads[nCar],&dwExitCode);
        CloseHandle(hThreads[nCar]);
    }

    for(nEquipe=0; nEquipe< EQUIPES; nEquipe++) CloseHandle(hMutex[nEquipe]);

    CloseHandle(hSemaphore);
    printf("\nPressione Qualquer tecla para terminar\n");

}

DWORD WINAPI FuncCar(LPVOID id){
    long lOldValue;
    int nCar, iTeam;

    iTeam = (DWORD)id % 256;
    nCar = (DWORD)id / 256;

    for(int i=0;i<3;i++){
        printf("Carro %d da equipe %d quer treindar... volta %d\n",nCar,iTeam, i); 

    //Aguardar a disponibilidade do Mutex
    WaitForSingleObject(hMutex[iTeam],INFINITE);

    //Aguardar disponibilidade do semáforo para decrementá-lo
    WaitForSingleObject(hSemaphore,INFINITE);

    printf("Carro %d da equipe %d treinando ... volta %d \n", nCar, iTeam, i);
    Sleep(100*(rand()%10));

    //Incrementar o semáforo
    ReleaseSemaphore(hSemaphore,1,&lOldValue);

    //Liberar o mutex
    ReleaseMutex(hMutex);
    printf("Carro %d da equipe %d acabou de treinar %d \n",nCar,iTeam,i);
    }
    // Terminar execução da Thread com código 0
    _endthreadex(0);
    return(0);
}
