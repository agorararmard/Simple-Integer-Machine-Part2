#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Parser.h"
#include "sizes.h"
#include "Instructions.h"
#include "Exceptions.h"
class Processor{
    private:
        int *dataMemory;
        std::mutex *ReadMutex;
        std::mutex *WriteMutex;
        std::mutex *memoryWrite;
        Instruction *instMemory[InstructionMemorySize];
        int pc;
        std::exception_ptr* myExceptionPtr;
    public:
 
 
        Processor(int* dm, std::mutex& rm, std::mutex& wm, std::mutex* mw, std::exception_ptr& myExceptionPtr):dataMemory(dm),ReadMutex(&rm),WriteMutex(&wm),memoryWrite(mw),myExceptionPtr(&myExceptionPtr){}
        void loadInstMem(std::string filename);         //loading a program file into the instruction memory
        void run();                                     //running the program in the instruction memory starting with pc = 0 
        
        //freeing instruction memory pointers.
        ~Processor(){
            for (int i =0; i < InstructionMemorySize;i++)
                if(instMemory[i] != nullptr)
                    delete instMemory[i];
                else
                    break;
        }
};
#include"Processor.cpp"
#endif