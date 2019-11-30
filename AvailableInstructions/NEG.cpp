#include"../sizes.h"
class negInstruction: public Instruction2Param{
    public:
    negInstruction(int& rs, bool isRsAddress,int& rd, bool isRdAddress,std::mutex &rdm ): Instruction2Param(rs, isRsAddress, rd, isRdAddress,rdm){
        if(!isRdAddress){
                throw ParamterShouldBeAddress("NEG", "2");
        }
    }
    virtual void exec(){
        if(isRdAddress) rdm->lock();
        *rd = -(*rs);
        if(isRdAddress) rdm->unlock();
    }
    ~negInstruction(){}
};