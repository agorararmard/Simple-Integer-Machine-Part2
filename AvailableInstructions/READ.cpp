#include"../sizes.h"
class readInstruction: public Instruction1Param{
    public:
    readInstruction(int& rs, bool isRsAddress,std::mutex &rdm,std::mutex &opm): Instruction1Param(rs, isRsAddress,rdm,opm){
        if(!isRsAddress){
                throw ParamterShouldBeAddress("READ", "1");
        }
    }
    virtual void exec(){
        rdm->lock();
        opm->lock();
        std::cin >> *rs;
        opm->unlock();
        rdm->unlock();
    }
    ~readInstruction(){}
};