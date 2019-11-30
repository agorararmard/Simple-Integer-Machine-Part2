#include "../sizes.h"
class jmp0Instruction: public Instruction3Param{
    public:
    jmp0Instruction(int& rs1, bool isRs1Address,int& rs2, bool isRs2Address,int& rd, bool isRdAddress ,std::mutex &rdm): Instruction3Param(rs1, isRs1Address, rs2, isRs2Address, rd, isRdAddress,rdm){
        if(isRs2Address){
            throw ParamterShouldBeAddress("JMP", "2");
        }
    }
    virtual void exec(){
        if(*rs2 <0 || *rs2 > InstructionMemorySize)
            throw OutOfInstructionMemoryBounds();
        if(!*rs1){
            *rd = *rs2 - 1;
        }
    }
    ~jmp0Instruction(){}
};