#include"../sizes.h"
#include"../Exceptions.h"
class writeInstruction: public Instruction1Param{
    public:
    writeInstruction(int& rs, bool isRsAddress,std::mutex &rdm,std::mutex &opm): Instruction1Param(rs, isRsAddress,rdm,opm){
    }
    virtual void exec(){
        opm->lock();
        std::cout << *rs <<std::endl;
        opm->unlock();
    }
    ~writeInstruction(){}
};