#include"../sizes.h"
#include"../Exceptions.h"
class readInstruction: public Instruction1Param{
    public:
    readInstruction(int& rs, bool isRsAddress,std::mutex &rdm,std::mutex &opm): Instruction1Param(rs, isRsAddress,rdm,opm){
        if(!isRsAddress){
                throw ParamterShouldBeAddress("READ", "1");
        }
    }
    virtual void exec(){
        if(rdm != nullptr) rdm->lock();
        if(opm != nullptr) opm->lock();
        
        std::cin >> *rs;

        if(rdm != nullptr) rdm->unlock();
        if(opm != nullptr) opm->unlock();
        
    }
    ~readInstruction(){}
};