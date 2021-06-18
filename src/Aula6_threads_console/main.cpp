#include "babythread.h"

using namespace std;

int main (int argc, char **argv){
	BabyThread *thr = new BabyThread();

    thread *threads = new thread[thr->MAX_THREAD_COUNT];

    for(int i=0;i<thr->MAX_THREAD_COUNT;i++)
        threads[i] = thr->spawn(i);

    for(int i=0;i<thr->MAX_THREAD_COUNT;i++)
        threads[i].join();

    return 0;	
}