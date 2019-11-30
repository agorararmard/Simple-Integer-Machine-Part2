#include"../sizes.h"
class writeInstruction: public Instruction1Param{
    public:
    writeInstruction(int& rs, bool isRsAddress): Instruction1Param(rs, isRsAddress){
    }
    virtual void exec(){
        std::cout << *rs <<std::endl;
    }
    ~writeInstruction(){}
};