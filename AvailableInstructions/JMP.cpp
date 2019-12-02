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
        if(rdm2 != nullptr){
            lck1 = new std::unique_lock<std::mutex>{*rdm1, std::defer_lock};
            lck2 = new std::unique_lock<std::mutex>{*rdm2, std::defer_lock};
            std::lock(*lck1,*lck2);
        }else{
            rdm1->lock();
        }
        if(*rs <0 || *rs > InstructionMemorySize){
            if(rdm2 != nullptr){
                delete lck1; 
                delete lck2; 
            }else{
                rdm1->unlock();
            }
            throw OutOfInstructionMemoryBounds();
        }
        
        *rd = (*rs) - 1;
        if(rdm2 != nullptr){
            delete lck1; 
            delete lck2; 
        }else{
            rdm1->unlock();
        }
    }
    ~jmpInstruction(){}
};