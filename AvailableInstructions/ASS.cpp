#include"../sizes.h"
#include "../Exceptions.h"
class assInstruction: public Instruction2Param{
    public:
    assInstruction(int& rs, bool isRsAddress,int& rd, bool isRdAddress ,std::mutex &rdm1,std::mutex &rdm2): Instruction2Param(rs, isRsAddress, rd, isRdAddress, rdm1,rdm2){
        if(!isRdAddress){
             throw ParamterShouldBeAddress("ASS", "2");
        }
    }
    virtual void exec(){
    
        if(rdm1 != nullptr) rdm1->lock();
        if(rdm2 != nullptr) rdm2->lock();
        
        *rd = *rs;
        
        if(rdm1 != nullptr) rdm1->unlock();
        if(rdm2 != nullptr) rdm2->unlock();
        
    }
    ~assInstruction(){}
};