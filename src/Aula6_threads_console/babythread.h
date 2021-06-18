#ifndef BABYTHREAD_H
#define BABYTHREAD_H

#include <iostream>
#include <thread>

class  BabyThread{
    public:
    // Uma variável só pode ser definida aqui se for static const int ou um enum
    // Para outras constantes, utilize a lista
    static const int MAX_THREAD_COUNT = 20;
    BabyThread();
    std::thread spawn (int tId);

    private:
    void showMsg(int tId);
};
#endif