#include "babythread.h"
#include <chrono>

using namespace std;
BabyThread::BabyThread(){}

thread BabyThread::spawn(int tId){ // Spawn é chamado ao rodar a thread
    return thread([&](){showMsg(tId);});
}

void BabyThread::showMsg(int tId){ // Dorme um tempo aleatório e exibe mensagem no fim
    this_thread::sleep_for(chrono::milliseconds(rand()%5000));
    cout<<"Esta eh a thread "<<tId<<"\n";
}

