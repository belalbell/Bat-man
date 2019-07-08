#include "BatFunctions.h"

//default constructor initializes the variables at the beginning
BatFunctions::BatFunctions(pthread_cond_t northQ, pthread_cond_t eastQ,
                           pthread_cond_t westQ, pthread_cond_t southQ, pthread_cond_t nFirst, pthread_cond_t eFirst,
                           pthread_cond_t wFirst, pthread_cond_t sFist, int nCounter, int sCounter,
                           int eCounter, int wCounter, int nFirstCounter, int eFirstCounter,
                           int wFirstCounter, int sFistCounter, pthread_mutex_t lk,
                           char dLockSeq) {
    NorthQueue = northQ;
    EastQueue = eastQ;
    WestQueu = westQ;
    SouthQueue = southQ;
    NorthFirst = nFirst;
    WestFirst = wFirst;
    EastFirst = eFirst;
    SouthFist = sFist;
    northCounter = nCounter;
    eastCounter = eCounter;
    westCounter = wCounter;
    southCounter = sCounter;
    NorthFirstCounter = nFirstCounter;
    WestFirstCounter = wFirstCounter;
    EastFirstCounter = eFirstCounter;
    SouthFistCounter = sFistCounter;
    lock = lk;
    deadLockSeq = dLockSeq;

}


void BatFunctions::arrive(char direction, int ID) { // handling the coming threads
    pthread_mutex_lock(&lock);
    if (direction == 'n') { // north threads
        northCounter++;
        cout << "BAT " << ID << " from " << direction << " entering arriving" << endl;
        if (northCounter > 0) { // check for waiting
            pthread_cond_wait(&NorthQueue, &lock);
        }
        cout << "BAT " << ID << " from " << direction << " arrives at crossing\n" << endl;
    } else if (direction == 'e') { // east threads
        eastCounter++;
        cout << "BAT " << ID << " from " << direction << " entering arriving" << endl;
        if (eastCounter > 0) { // check for waiting
            pthread_cond_wait(&EastQueue, &lock);
        }
        cout << "BAT " << ID << " from " << direction << " arrives at crossing\n" << endl;
    } else if (direction == 's') { // south threads
        southCounter++;
        cout << "BAT " << ID << " from " << direction << " entering arriving" << endl;
        if (southCounter > 0) { // check for waiting
            pthread_cond_wait(&SouthQueue, &lock);
        }
        cout << "BAT " << ID << " from " << direction << " arrives at crossing\n" << endl;
    } else if (direction == 'w') { // west threads
        westCounter++;
        cout << "BAT " << ID << " from " << direction << " entering arriving" << endl;
        if (westCounter > 0) { // check for waiting
            pthread_cond_wait(&WestQueu, &lock);
        }
        cout << "BAT " << ID << " from " << direction << " arrives at crossing\n" << endl;

    }
    pthread_mutex_unlock(&lock);

}

void BatFunctions::cross(char direction, int ID) { // handling the crossing threads
    pthread_mutex_lock(&lock);

    DeadLock deadLock(deadLockSeq, NorthFirstCounter, EastFirstCounter, WestFirstCounter, SouthFistCounter,
                      NorthFirst, EastFirst, WestFirst, SouthFist);

    cout << ID << " in crossing " << endl;
    //north check on west
    if (direction == 'n' && westCounter >= 0) {

        if (SouthFistCounter == 0) {
            pthread_cond_signal(&WestQueu);
        }
        if (deadLock.check()) {
            if (deadLockSeq != 'n') {//change the sequence for solving the dead lck each time to avoid starvation
                deadLockSeq = 'n';
            }
            //deadLock.solveDeadLock();
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
        cout << "bat " << ID << " in west first queue" << endl;
        WestFirstCounter++;
        pthread_cond_wait(&WestFirst, &lock);

    }
    //west check on south
    if (direction == 'w' && southCounter >= 0) {

        if (EastFirstCounter == 0) {
            pthread_cond_signal(&SouthQueue);
        }
        if (deadLock.check()) {
            if (deadLockSeq != 'w') {
                deadLockSeq = 'w';
            }
            //deadLock.solveDeadLock();
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
        cout << ID << " in south first queue" << endl;
        SouthFistCounter++;
        pthread_cond_wait(&SouthFist, &lock);


    }
    //south check on east
    if (direction == 's' && eastCounter >= 0) {
        if (NorthFirstCounter == 0) {
            pthread_cond_signal(&EastQueue);
        }
        if (deadLock.check()) {
            if (deadLockSeq != 's') {
                deadLockSeq = 's';
            }
            //deadLock.solveDeadLock();
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
        cout << ID << " in east first queue" << endl;
        EastFirstCounter++;
        pthread_cond_wait(&EastFirst, &lock);

    }
    //east check on north
    if (direction == 'e' && northCounter >= 0) {
        if (WestFirstCounter == 0) {
            pthread_cond_signal(&NorthQueue);
        }
        if (deadLock.check()) {
            if (deadLockSeq != 'e') {
                deadLockSeq = 'e';
            }
            //deadLock.solveDeadLock();
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
        cout << ID << " in north first queue" << endl;
        NorthFirstCounter++;
        pthread_cond_wait(&NorthFirst, &lock);

    }
    pthread_mutex_unlock(&lock);
    cout << ID << " will go to sleep" << endl;
    sleep(1);
    //cout << "BAT " << id << " from " << direction << " crossing" << endl;
    cout << ID << " finish sleeping" << endl;
}


void BatFunctions::leave(char direction, int ID) { // handling leaving threads
    cout << ID << " leaving " << endl;
    pthread_mutex_lock(&lock);
    if (direction == 'n') { // north threads
        if (northCounter > 0) { // checking for signal the next thread in the north queue or not
            if (WestFirstCounter == 0) {
                pthread_cond_signal(&NorthQueue);
            }
            northCounter--;
            cout << "BAT " << ID << " from " << direction << " (if) leaving crossing\n" << endl;
        } else { // to signal from first queue
            pthread_cond_signal(&NorthFirst);
            NorthFirstCounter--;
            northCounter--;
            cout << "BAT " << ID << " from " << direction << " (else) leaving crossing\n" << endl;
        }
    } else if (direction == 'w') { // west threads
        if (westCounter > 0) {// checking for signal the next thread in the west queue or not
            if (SouthFistCounter == 0) {
                pthread_cond_signal(&WestQueu);
            }
            westCounter--;
            cout << "BAT " << ID << " from " << direction << " (if)leaving crossing\n" << endl;
        } else { //to signal from the first queue
            pthread_cond_signal(&WestFirst);
            WestFirstCounter--;
            westCounter--;
            cout << "BAT " << ID << " from " << direction << " (else)leaving crossing\n" << endl;
        }
    } else if (direction == 's') {//south threads
        if (southCounter > 0) {// checking for signal the next thread in the south queue or not
            if (EastFirstCounter == 0) {
                pthread_cond_signal(&SouthQueue);
            }
            southCounter--;
            cout << "BAT " << ID << " from " << direction << " (if)leaving crossing\n" << endl;
        } else { // to signal from the first queue
            pthread_cond_signal(&SouthFist);
            SouthFistCounter--;
            southCounter--;
            cout << "BAT " << ID << " from " << direction << " (else)leaving crossing\n" << endl;
        }
    } else if (direction == 'e') { // east threads
        if (eastCounter > 0) {// checking for signal the next thread in the east queue or not
            if (NorthFirstCounter == 0) {
                pthread_cond_signal(&EastQueue);
            }
            eastCounter--;
            cout << "BAT " << ID << " from " << direction << " (if)leaving crossing\n" << endl;
        } else { // to signal from first queu
            pthread_cond_signal(&EastFirst);
            EastFirstCounter--;
            eastCounter--;
            cout << "BAT " << ID << " from " << direction << " (else)leaving crossing\n" << endl;
        }
    }
    pthread_mutex_unlock(&lock);
}

