#ifndef BATTEMP_DEADLOCK_H
#define BATTEMP_DEADLOCK_H

#include <iostream>
#include <mutex>
#include <pthread.h>
#include <unistd.h>

using namespace std;

class DeadLock {

private:
    int NorthFirstCounter, EastFirstCounter, WestFirstCounter, SouthFistCounter; //counters for the first queues
    char deadLockSeq; //sequence to solve starvation
    pthread_cond_t NorthFirst, EastFirst, WestFirst, SouthFist;

public:
    //default constructor
    DeadLock(char, int, int, int, int, pthread_cond_t, pthread_cond_t, pthread_cond_t, pthread_cond_t);

    void solveDeadLock();

    bool check();

};


#endif //BATTEMP_DEADLOCK_H
