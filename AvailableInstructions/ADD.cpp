#include"../sizes.h"
#include "../Exceptions.h"
class addInstruction: public Instruction3Param{
    public:
    addInstruction(int& rs1, bool isRs1Address,int& rs2, bool isRs2Address,int& rd, bool isRdAddress,std::mutex &rdm ): Instruction3Param(rs1, isRs1Address, rs2, isRs2Address, rd, isRdAddress,rdm){
        if(!isRdAddress){
            throw ParamterShouldBeAddress("ADD", "3");
        }
    }
    virtual void exec(){
        int tmp1 = *rs1;
        int tmp2 = *rs2;

        if(isRdAddress) rdm->lock();
        *rd = *rs1 + *rs2;
        if(isRdAddress) rdm->unlock();
        if(*rd - tmp1 != tmp2) //for detecting overflow
            throw OverFlow();
    }
    ~addInstruction(){}
};