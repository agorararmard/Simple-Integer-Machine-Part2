#include"../sizes.h"
#include "../Exceptions.h"
class assInstruction: public Instruction2Param{
    public:
    assInstruction(int& rs, bool isRsAddress,int& rd, bool isRdAddress ,std::mutex &rdm): Instruction2Param(rs, isRsAddress, rd, isRdAddress, rdm){
        if(!isRdAddress){
             throw ParamterShouldBeAddress("ASS", "2");
        }
    }
    virtual void exec(){
        if(isRdAddress) rdm->lock();
        *rd = *rs;
        if(isRdAddress) rdm->unlock();
    }
    ~assInstruction(){}
};