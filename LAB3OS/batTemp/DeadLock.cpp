#include "DeadLock.h"

DeadLock::DeadLock(char dLockSeq, int nFirstCounter, int eFirstCounter,
                   int wFirstCounter, int sFistCounter, pthread_cond_t nFirst, pthread_cond_t eFirst,
                   pthread_cond_t wFirst, pthread_cond_t sFist) {
    deadLockSeq = dLockSeq;
    NorthFirstCounter = nFirstCounter;
    WestFirstCounter = wFirstCounter;
    EastFirstCounter = eFirstCounter;
    SouthFistCounter = sFistCounter;
    NorthFirst = nFirst;
    WestFirst = wFirst;
    EastFirst = eFirst;
    SouthFist = sFist;
}

// the method used to solve deadlock and avoid starvation
void DeadLock::solveDeadLock() {
    if (deadLockSeq == 'n') {
        deadLockSeq = 'w';
        pthread_cond_signal(&NorthFirst);
        NorthFirstCounter--;
    } else if (deadLockSeq == 'w') {
        deadLockSeq = 's';
        pthread_cond_signal(&WestFirst);
        WestFirstCounter--;
    } else if (deadLockSeq == 's') {
        deadLockSeq = 'e';
        pthread_cond_signal(&SouthFist);
        SouthFistCounter--;
    } else if (deadLockSeq == 'e') {
        deadLockSeq = 'n';
        pthread_cond_signal(&EastFirst);
        EastFirstCounter--;
    }
}

// check to avoid deadlock if there is 3 of the first queues are full
bool DeadLock::check() {
    if ((NorthFirstCounter > 0 && EastFirstCounter > 0 && SouthFistCounter > 0)) {
        cout << "DEADLOCK: BAT jam detected" << endl;
        return true;
    } else if (NorthFirstCounter > 0 && EastFirstCounter > 0 && WestFirstCounter > 0) {
        cout << "DEADLOCK: BAT jam detected" << endl;
        return true;
    } else if (NorthFirstCounter > 0 && SouthFistCounter > 0 && WestFirstCounter > 0) {
        cout << "DEADLOCK: BAT jam detected" << endl;
        return true;
    } else if (EastFirstCounter > 0 && SouthFistCounter > 0 && WestFirstCounter > 0) {
        cout << "DEADLOCK: BAT jam detected" << endl;
        return true;
    }
    return false;
}

