#include "Processor.h"


void Processor::loadInstMem(std::string filename){
    int *d =dataMemory;
    Instruction **i = instMemory;
    Parser P(d,i,pc, filename,ReadMutex,WriteMutex,memoryWrite);
    try{
    P.readInstMem();
    }catch(std::exception& exp){
        std::cout << exp.what() << std::endl;
        throw;
    }
}


void Processor::run(){
    pc =0;
    while(true){
        try{
            if(pc == InstructionMemorySize) return;
            WriteMutex->lock();
            std::cout << "\nProgram Counter: " << pc<< " Input/Output ---> ";
            WriteMutex->unlock();
            if(instMemory[pc] == nullptr)   throw NullInstruction();
            instMemory[pc]->exec();
            pc++;
        }catch(std::runtime_error& exp){
            std::string s1 = HALTException().what(); 
            std::string s2 = exp.what(); 
            if(s2 == s1)
            {
                std::cout << s2 << std::endl;
                return;
            }
            else {
                std::cout << s2 << std::endl;
                throw;    
            }
        }
    }
}