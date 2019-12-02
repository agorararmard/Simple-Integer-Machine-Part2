#include"../sizes.h"
#include"../Exceptions.h"
class leInstruction: public Instruction3Param{
    public:
    leInstruction(int& rs1, bool isRs1Address,int& rs2, bool isRs2Address,int& rd, bool isRdAddress ,std::mutex &rdm1,std::mutex &rdm2,std::mutex &rdm3): Instruction3Param(rs1, isRs1Address, rs2, isRs2Address, rd, isRdAddress,rdm1,rdm2,rdm3){
        if(!isRdAddress){
            throw ParamterShouldBeAddress("LE", "3");
        }
    }
    virtual void exec(){
        if(rdm1 != nullptr) rdm1->lock();
        if(rdm2 != nullptr) rdm2->lock();
        if(rdm3 != nullptr) rdm3->lock();
        
          *rd = (*rs1 <=*rs2)? 1:0;
        if(rdm1 != nullptr) rdm1->unlock();
        if(rdm2 != nullptr) rdm2->unlock();
        if(rdm3 != nullptr) rdm3->unlock();
        
    }
    ~leInstruction(){}
};