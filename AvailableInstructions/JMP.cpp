#include "../sizes.h"
#include "../Exceptions.h"
class jmpInstruction: public Instruction2Param{
    public:
    jmpInstruction(int& rs, bool isRsAddress,int& rd, bool isRdAddress ,std::mutex &rdm1,std::mutex &rdm2): Instruction2Param(rs, isRsAddress, rd, isRdAddress,rdm1,rdm2){
        if(isRsAddress){
                throw ParamterShouldBeAddress("JMP", "1");
        }
    }
    virtual void exec(){
        
        std::unique_lock<std::mutex> *lck1,*lck2;
        if(rdm1 != nullptr) rdm1->lock();
        if(rdm2 != nullptr) rdm2->lock();
        
        if(*rs <0 || *rs > InstructionMemorySize){
        if(rdm1 != nullptr) rdm1->unlock();
        if(rdm2 != nullptr) rdm2->unlock();
        
            throw OutOfInstructionMemoryBounds();
        }
        
        *rd = (*rs) - 1;
        if(rdm1 != nullptr) rdm1->unlock();
        if(rdm2 != nullptr) rdm2->unlock();
        
        
    }
    ~jmpInstruction(){}
};