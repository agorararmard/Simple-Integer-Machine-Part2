#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Parser.h"
#include "sizes.h"
#include "Instructions.h"
#include "Exceptions.h"
class Proccessor{
    private:
        int *dataMemory;
        Instruction *instMemory[InstructionMemorySize];
        int pc;
    public:
        Proccessor(int* dm):dataMemory(dm){}
        void loadInstMem(std::string filename);         //loading a program file into the instruction memory
        void run();                                     //running the program in the instruction memory starting with pc = 0
        
        //freeing instruction memory pointers.
        ~Proccessor(){
            for (int i =0; i < InstructionMemorySize;i++)
                if(instMemory[i] != nullptr)
                    delete instMemory[i];
                else
                    break;
        }
};
#include"Processor.cpp"
#endif