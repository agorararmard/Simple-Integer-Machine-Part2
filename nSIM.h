#ifndef NSIM_H
#define NSIM_H

#include"Processor.h"
#include <iostream>
#include <string>
#include <thread>
class nSIM{
    private:
        int n;  //number of processors
        int dataMemory[dataMemorySize];
        Proccessor** cores;
    public:
        nSIM(int numberOfCores);  
        void load();
        void run();
        ~nSIM();
};

#include"nSIM.cpp"
#endif