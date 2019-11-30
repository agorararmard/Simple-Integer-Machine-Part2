#ifndef PARSER_H
#define PARSER_H
#include "InstructionFactory.h"
#include <string>
#include <fstream>
class Parser{
    private:
        InstructionFactory instFactory;
        int* dataMemory;
        Instruction** instMemory;
        int* pc;
        std::mutex *ReadMutex;
        std::mutex *WriteMutex;
        std::mutex *memoryWrite;

       
        std::string fileInst;
       
        void getInstructionType(std::string& line,std::string& instType);       //Function to get the instruction type from the read line as string
        void getFirstParameter(std::string& line,std::string& firstParam);      //Function to get the first paramater from the read line as string
        void getSecondParameter(std::string& line,std::string& secondParam);    //Function to get the second paramater from the read line as string
        void getThirdParameter(std::string& line,std::string& thirdParam);      //Function to get the third paramater from the read line as string

    public:
        // pointers to the instruction and data memory and to the pc. To write the instructions properly in terms of references
        Parser(int* &dataMemory,Instruction** &instMemory,int& pc, std::string fileInst, std::mutex* &rm, std::mutex* &wm, std::mutex* &mw):dataMemory(dataMemory),instMemory(instMemory),pc(&pc),fileInst(fileInst),ReadMutex(rm),WriteMutex(wm),memoryWrite(mw){}
        
        void readInstMem();//Function to read a program file and load it into the instruction memory;

        ~Parser(){} //no memory to free.


};
#include"Parser.cpp"
#endif