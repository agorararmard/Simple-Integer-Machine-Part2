#include "../sizes.h"
#include "../Exceptions.h"
class jmp0Instruction: public Instruction3Param{
    public:
    jmp0Instruction(int& rs1, bool isRs1Address,int& rs2, bool isRs2Address,int& rd, bool isRdAddress ,std::mutex &rdm1,std::mutex &rdm2,std::mutex &rdm3): Instruction3Param(rs1, isRs1Address, rs2, isRs2Address, rd, isRdAddress,rdm1,rdm2,rdm3){
        if(isRs2Address){
            throw ParamterShouldBeAddress("JMP", "2");
        }
    }
    virtual void exec(){

        if(rdm1 != nullptr) rdm1->lock();
        if(rdm2 != nullptr) rdm2->lock();
        if(rdm3 != nullptr) rdm3->lock();
        
        if(*rs2 <0 || *rs2 > InstructionMemorySize){
            if(rdm1 != nullptr) rdm1->unlock();
            if(rdm2 != nullptr) rdm2->unlock();
            if(rdm3 != nullptr) rdm3->unlock();
            
            throw OutOfInstructionMemoryBounds();
        }
   
        if(!*rs1){
            *rd = *rs2 - 1;
        }
        if(rdm1 != nullptr) rdm1->unlock();
        if(rdm2 != nullptr) rdm2->unlock();
        if(rdm3 != nullptr) rdm3->unlock();
   
    }
    ~jmp0Instruction(){}
};