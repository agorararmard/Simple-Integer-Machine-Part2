#include "../sizes.h"
#include "../Exceptions.h"
class jmpInstruction: public Instruction2Param{
    public:
    jmpInstruction(int& rs, bool isRsAddress,int& rd, bool isRdAddress ,std::mutex &rdm): Instruction2Param(rs, isRsAddress, rd, isRdAddress,rdm){
        if(isRsAddress){
                throw ParamterShouldBeAddress("JMP", "1");
        }
    }
    virtual void exec(){
        if(*rs <0 || *rs > InstructionMemorySize)
            throw OutOfInstructionMemoryBounds();
        
        *rd = (*rs) - 1;
    }
    ~jmpInstruction(){}
};