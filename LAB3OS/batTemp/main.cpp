#include <iostream>
#include <mutex>
#include <pthread.h>
#include <unistd.h>
#include "Monitor.h"

using namespace std;

 Monitor batman;

void *execute(void *parameters);
void joinThreads(pthread_t threads [] , int numberOfThreads);

int main() {
    cout<<"Enter the input sequence : ";
    string input;
    cin>>input;
    int numberOfThreads =input.size();
    pthread_t threads[numberOfThreads];

    for (int index = 0; index < input.size(); index++) {
        //pthread_t bat;
        //threads[index] = bat;
        char *batParameters = new char[2];
        batParameters[0] = index; //bat ID
        batParameters[1] = input[index];//bat direction
        pthread_create(&threads[index], NULL, execute, (void *) batParameters);
    }

    joinThreads(threads,numberOfThreads);

    return 0;
}

// the execution method for the threads
void *execute(void *parameters) {
    char *info = (char *) parameters;
    char direction = info[1];
    int id = info[0];
    batman.arrive(direction, id);
    batman.cross(direction, id);
    batman.leave(direction, id);
}

void joinThreads(pthread_t threads [] , int numberOfThreads){
    for (int index = 0; index < numberOfThreads; index++) {
        pthread_join(threads[index], NULL);
    }
}