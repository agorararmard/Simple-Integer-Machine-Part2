#include"../sizes.h"
class negInstruction: public Instruction2Param{
    public:
    negInstruction(int& rs, bool isRsAddress,int& rd, bool isRdAddress ): Instruction2Param(rs, isRsAddress, rd, isRdAddress){
        if(!isRdAddress){
                throw ParamterShouldBeAddress("NEG", "2");
        }
    }
    virtual void exec(){
        *rd = -(*rs);
    }
    ~negInstruction(){}
};