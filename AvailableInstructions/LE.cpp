#include"../sizes.h"
class leInstruction: public Instruction3Param{
    public:
    leInstruction(int& rs1, bool isRs1Address,int& rs2, bool isRs2Address,int& rd, bool isRdAddress ): Instruction3Param(rs1, isRs1Address, rs2, isRs2Address, rd, isRdAddress){
        if(!isRdAddress){
            throw ParamterShouldBeAddress("LE", "3");
        }
    }
    virtual void exec(){
        *rd = (*rs1 <=*rs2)? 1:0;
    }
    ~leInstruction(){}
};