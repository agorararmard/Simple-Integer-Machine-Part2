#include "nSIM.h"

nSIM::nSIM(int numberOfCores):n(numberOfCores){
    cores = new Processor*[n];
    for(int i =0;i < n;i++)
        cores[i] = new Processor(dataMemory,ReadMutex,WriteMutex,memoryWrite);
}
void nSIM::load(){
    std::string filename;
    std::thread *threads = new std::thread[n];
    try{
        for(int i =0; i < n;i++){
            std::cin >> filename;
            threads[i] = std::thread(&Processor::loadInstMem,cores[i],filename);
            cores[i]->loadInstMem(filename);
        }
        for(int i =0; i < n;i++){
            threads[i].join();
        }
        delete[] threads;
    }catch(std::exception& exp){
        std::cout << exp.what() << std::endl;
        throw;
    }
}

void nSIM::run(){
    std::thread *threads = new std::thread[n];
    try{
        for(int i =0; i < n;i++){
            threads[i] = std::thread(&Processor::run,cores[i]);
            //cores[i]->run();
        }
        for(int i =0; i < n;i++){
            threads[i].join();
        }
        delete[] threads;
    }catch(std::runtime_error& exp){
        std::cout << exp.what() << std::endl;
        throw;
    }
}       
nSIM::~nSIM(){
    for(int i =0;i < n;i++)
        delete cores[i];
    std::cout << "Done that!\n";
    delete[] cores;
}