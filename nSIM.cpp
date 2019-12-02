#include "nSIM.h"

nSIM::nSIM(int numberOfCores):n(numberOfCores){
    cores = new Processor*[n];
    ExceptionPtr = new std::exception_ptr[n];
    for(int i =0;i < n;i++){
        //ExceptionPtr[i] = nullptr;
        cores[i] = new Processor(dataMemory,ReadMutex,WriteMutex,memoryWrite, ExceptionPtr[i]);
    }
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
        std::cout <<"walahi 3detohom\b";
        for(int i =0; i < n;i++){
            if(ExceptionPtr[i] != nullptr)
                 std::rethrow_exception(ExceptionPtr[i]);
            if(threads[i].joinable())
                threads[i].join();
        }

        delete[] threads;
    }catch(std::exception& exp){
        std::cout << exp.what() << std::endl;

        for(int i =0; i < n;i++){
            if(threads[i].joinable())
                threads[i].join();
        }

        delete[] threads;
        
        throw;
    }
}

void nSIM::run(){
    std::thread *threads = new std::thread[n];
    try{
        for(int i =0; i < n;i++){
            threads[i] = std::thread(&Processor::run,cores[i]);
        }
        
        for(int i =0; i < n;i++){
            if(ExceptionPtr[i] != nullptr)
                 std::rethrow_exception (ExceptionPtr[i]);
           
            if(threads[i].joinable())
                threads[i].join();
        }
        
        delete[] threads;
    
    }catch(std::exception& exp){
        std::cout << exp.what() << std::endl;
        
        for(int i =0; i < n;i++){
            if(threads[i].joinable())
                threads[i].join();
        }

        delete[] threads;
       
        throw;
    }
}       
nSIM::~nSIM(){
    for(int i =0;i < n;i++)
        delete cores[i];
    std::cout << "Done that!\n";
    delete[] cores;
}