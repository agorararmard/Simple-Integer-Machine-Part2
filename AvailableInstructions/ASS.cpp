#include"../sizes.h"
#include "../Exceptions.h"
class assInstruction: public Instruction2Param{
    public:
    assInstruction(int& rs, bool isRsAddress,int& rd, bool isRdAddress ): Instruction2Param(rs, isRsAddress, rd, isRdAddress){
        if(!isRdAddress){
             throw ParamterShouldBeAddress("ASS", "2");
        }
    }
    virtual void exec(){
        *rd = *rs;
    }
    ~assInstruction(){}
};