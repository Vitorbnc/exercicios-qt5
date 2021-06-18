#include "textthread.h"

TextThread::TextThread(int threadId):id(threadId)
{
    pauseRequested = false;
}

// A thread retorna uma string a cada 3 segundos. Sua execução pode ser pausada ou interrompida
void TextThread::run(){
    while(true && !isInterruptionRequested()){
        msleep(3000);
        if(!pauseRequested){
            if(isInterruptionRequested()) return;
            emit resultReady(QString("Executando loop da thread %1 \n").arg(id));
        }
        else msleep(333); // Sem sleep a thread fica em loop contínuo e usa muita CPU quando em pausa
    }
    //emit finished();
}
