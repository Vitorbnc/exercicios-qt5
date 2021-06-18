#include "vehicle.h"
#include <QThread>
#include <QTextStream>


//Inicialização de membro estático
QSemaphore Vehicle::sem(MAX_COUNT);
int Vehicle::count = 0;

Vehicle::Vehicle(QString equipe, int t):equipe(equipe),lapInterval(t),abortRequested(false){
    count++;
    //Recomendado pela Documentação, marca para deleção após término
    setAutoDelete(true);
}

Vehicle::~Vehicle(){
    count--;
    emit sendMsg(""); // mensagem em branco apenas para emitir um sinal na destruição
}

void Vehicle::requestAbort(){
    abortRequested = true;
    finish();
}

Moto::Moto(QString equipe,int t):Vehicle(equipe,t){}

void Moto::init(){
    emit  sendMsg(QString("Equipe de Moto ").append(equipe).append( " criada\n"));
}

Carro::Carro(QString equipe, int t):Vehicle(equipe,t){}

void Carro::init(){
    emit sendMsg(QString("Equipe de Carro ").append(equipe).append( " criada\n"));
}

void Moto::finish(){
    char s[] = "Equipe de Moto %s finalizou o treino.          \n";
    sprintf(s,s,equipe.toStdString().c_str());
    emit sendMsg(s);
}

void Moto::run(){

    for(int i=0;i<MAX_LAPS;i++){
        if(abortRequested) return;
        //tenta adquirir o semáforo, bloqueia se não der
        sem.acquire(1);
        char s[] = "Moto da Equipe %s treinando na volta %d          \n";
        sprintf(s,s,equipe.toStdString().c_str(),i);
        emit sendMsg(s);
        //Para melhorar o tempo de resposta, vamos fazer vários delays pequenos em vez de um grande
        for(int t=0;t<lapInterval;t+=100){
            if(abortRequested) {
                sem.release(1);
                return;
            }
            else QThread::msleep(lapInterval>100?lapInterval/100:lapInterval);
        }
        sem.release(1);
    }
    finish();
}

void Carro::finish(){
    char s[] = "Equipe de Carro %s finalizou o treino.          \n";
    sprintf(s,s,equipe.toStdString().c_str());
    emit sendMsg(s);
}

void Carro::run(){

    for(int i=0;i<MAX_LAPS;i++){
        if(abortRequested) return;
        sem.acquire(1);
        char s[] = "Carro da Equipe %s treinando na volta %d          \n";
        sprintf(s,s,equipe.toStdString().c_str(),i);
        emit sendMsg(s);
        //Para melhorar o tempo de resposta, vamos fazer vários delays pequenos em vez de um grande
        for(int t=0;t<lapInterval;t+=100){
            if(abortRequested) {
                sem.release(1);
                return;
            }
            else QThread::msleep(lapInterval>100?lapInterval/100:lapInterval);
        }
        sem.release(1);
    }
    finish();
}
