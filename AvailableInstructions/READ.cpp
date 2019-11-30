#include"../sizes.h"
class readInstruction: public Instruction1Param{
    public:
    readInstruction(int& rs, bool isRsAddress): Instruction1Param(rs, isRsAddress){
        if(!isRsAddress){
                throw ParamterShouldBeAddress("READ", "1");
        }
    }
    virtual void exec(){
        std::cin >> *rs;
    }
    ~readInstruction(){}
};