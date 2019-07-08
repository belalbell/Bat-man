#ifndef BATTEMP_BATFUNCTIONS_H
#define BATTEMP_BATFUNCTIONS_H

#include <iostream>
#include <mutex>
#include <pthread.h>
#include <unistd.h>
#include "DeadLock.h"


using namespace std;

class BatFunctions {
private:
    pthread_cond_t NorthQueue, EastQueue, WestQueu, SouthQueue
    , NorthFirst, EastFirst, WestFirst, SouthFist;//conditions for the monitor
    int northCounter, southCounter, eastCounter, westCounter; // counters for the queues
    int NorthFirstCounter, EastFirstCounter, WestFirstCounter, SouthFistCounter; //counters for the first queues
    pthread_mutex_t lock; // the monitor mutex
    char deadLockSeq; //sequence to solve starvation

public:
    //default constructor
    BatFunctions( pthread_cond_t, pthread_cond_t, pthread_cond_t, pthread_cond_t, pthread_cond_t,
                 pthread_cond_t, pthread_cond_t, pthread_cond_t, int, int, int, int, int, int, int, int,
                 pthread_mutex_t, char);

    void arrive(char,int);

    void cross(char,int);

    void leave(char,int);
};


#endif //BATTEMP_BATFUNCTIONS_H
