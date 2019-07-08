#include "Monitor.h"

pthread_cond_t NorthQueue, EastQueue, WestQueu, SouthQueue //conditions for the monitor
, NorthFirst, EastFirst, WestFirst, SouthFist;
int northCounter = -1, southCounter = -1, eastCounter = -1, westCounter = -1; // counters for the queues
int NorthFirstCounter, EastFirstCounter, WestFirstCounter, SouthFistCounter; //counters for the first queues
pthread_mutex_t lck; // the monitor mutex
char deadLockSeq = 'n'; //sequence to solve starvation

Monitor::Monitor() {
    pthread_mutex_init(&lck, NULL);
    pthread_cond_init(&NorthQueue, NULL);
    pthread_cond_init(&EastQueue, NULL);
    pthread_cond_init(&WestQueu, NULL);
    pthread_cond_init(&SouthQueue, NULL);
    pthread_cond_init(&NorthFirst, NULL);
    pthread_cond_init(&EastFirst, NULL);
    pthread_cond_init(&WestFirst, NULL);
    pthread_cond_init(&SouthFist, NULL);

}

BatFunctions batFunctions(NorthQueue, EastQueue, WestQueu, SouthQueue, NorthFirst,
                          EastFirst, WestFirst, SouthFist, northCounter, southCounter, eastCounter,
                          westCounter, NorthFirstCounter, EastFirstCounter, WestFirstCounter,
                          SouthFistCounter, lck, deadLockSeq);

DeadLock deadLock(deadLockSeq, NorthFirstCounter, EastFirstCounter, WestFirstCounter,
                  SouthFistCounter, NorthFirst, EastFirst, WestFirst, SouthFist);

//arrive
void Monitor::arrive(char direction, int id) {
    batFunctions.arrive(direction, id);
}

//cross
void Monitor::cross(char direction, int id) {
    batFunctions.cross(direction, id);
}

//leave
void Monitor::leave(char direction, int id) {
    batFunctions.leave(direction, id);
}

////solve deadlock
//void static solveDeadLock() {
//    deadLock.solveDeadLock();
//}
//
////check for the deadlock
//bool static check() {
//    deadLock.check();
//}
