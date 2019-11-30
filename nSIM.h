#ifndef NSIM_H
#define NSIM_H

#include"Processor.h"
#include <thread>
class nSIM{
    private:
        int n;  //number of processors
        int dataMemory[dataMemorySize];
        Processor** cores;
        std::mutex ReadMutex;
        std::mutex WriteMutex;
        std::mutex memoryWrite[dataMemorySize];
    public:
        nSIM(int numberOfCores);  
        void load();
        void run();
        ~nSIM();
};

#include"nSIM.cpp"
#endif