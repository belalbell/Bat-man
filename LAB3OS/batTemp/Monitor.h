#ifndef BATTEMP_MONITOR_H
#define BATTEMP_MONITOR_H

#include <iostream>
#include <mutex>
#include <pthread.h>
#include <unistd.h>
#include "DeadLock.h"
#include "BatFunctions.h"

using namespace std;

class Monitor {

public:
    // default constructor
    Monitor();

    void arrive(char direction, int id);

    void cross(char direction, int id);

    void leave(char direction, int id);

private:


};


#endif //BATTEMP_MONITOR_H
