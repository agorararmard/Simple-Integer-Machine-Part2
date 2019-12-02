#include"../sizes.h"
#include "../Exceptions.h"

class addInstruction: public Instruction3Param{
    public:
    addInstruction(int& rs1, bool isRs1Address,int& rs2, bool isRs2Address,int& rd, bool isRdAddress,std::mutex &rdm1,std::mutex &rdm2,std::mutex &rdm3 ): Instruction3Param(rs1, isRs1Address, rs2, isRs2Address, rd, isRdAddress,rdm1,rdm2,rdm3){
        if(!isRdAddress){
            throw ParamterShouldBeAddress("ADD", "3");
        }
    }
    virtual void exec(){

    if(rdm1 != nullptr) rdm1->lock();
    if(rdm2 != nullptr) rdm2->lock();
    if(rdm3 != nullptr) rdm3->lock();
        int tmp1 = *rs1;
        int tmp2 = *rs2;

        *rd = *rs1 + *rs2;
        int tmp3 = *rd;
       if(rdm1 != nullptr) rdm1->unlock();
        if(rdm2 != nullptr) rdm2->unlock();
        if(rdm3 != nullptr) rdm3->unlock();

        if(tmp3 - tmp1 != tmp2) //for detecting overflow
            throw OverFlow();
     
          
    }
    ~addInstruction(){}
};