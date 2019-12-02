#include"../sizes.h"
class Instruction2Param: public Instruction{
    protected:
        int *rd;    //rd is always an address
        int *rs;
        bool isRdAddress;
        bool isRsAddress;
        std::mutex *rdm1;
        std::mutex *rdm2;
    public:
    Instruction2Param(int& rs, bool isRsAddress,int& rd, bool isRdAddress,std::mutex &rdm1,std::mutex &rdm2):rd(&rd),isRdAddress(isRdAddress),rs(&rs),isRsAddress(isRsAddress),rdm1(&rdm1),rdm2(&rdm2){

    }


    virtual void exec()=0;

    //Destructor will free the memory if the value was an immediate.
    virtual~Instruction2Param(){
        if(!isRdAddress) delete rd;
        if(!isRsAddress) delete rs;
    };    //here the destructor of P is called so there is no need to do anything
};