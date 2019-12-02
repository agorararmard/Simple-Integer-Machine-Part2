#include"../sizes.h"
#include"../Exceptions.h"
class writeInstruction: public Instruction1Param{
    public:
    writeInstruction(int& rs, bool isRsAddress,std::mutex &rdm,std::mutex &opm): Instruction1Param(rs, isRsAddress,rdm,opm){
    }
    virtual void exec(){
        
        if(rdm != nullptr) rdm->lock();
        if(opm != nullptr) opm->lock();
        
        std::cout << *rs <<std::endl;
        
        if(rdm != nullptr) rdm->unlock();
        if(opm != nullptr) opm->unlock();
        
    }
    ~writeInstruction(){}
};