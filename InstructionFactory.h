#ifndef INSTRUCTIONFACTORY_H
#define INSTRUCTIONFACTORY_H
#include "sizes.h"
#include "Instructions.h"
#include "Exceptions.h"
#include <cstdlib>

class InstructionFactory
{
private:
    int convertToInt(std::string s);    //convert a string to an integer. Report an error in case of failure i.e. the string is not a number
    bool interpretParam(std::string &param,int* &p,int* &dataMemory);   //translate the paramter into a memory reference or an immediate
public:
    InstructionFactory(){}
    //return an Instruction pointer after paramter validation according to instType.
    Instruction* createInstruction(std::string instType, std::string firstParam, std::string secondParam, std::string thirdParam,int&pc, int* &dataMemory);
    ~InstructionFactory(){}
};

#include"InstructionFactory.cpp"
#endif