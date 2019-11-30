#include"../sizes.h"
class Instruction2Param: public Instruction{
    protected:
        int *rd;    //rd is always an address
        int *rs;
        bool isRdAddress;
        bool isRsAddress;
    public:
    Instruction2Param(int& rs, bool isRsAddress,int& rd, bool isRdAddress):rd(&rd),isRdAddress(isRdAddress),rs(&rs),isRsAddress(isRsAddress){

    }


    virtual void exec()=0;

    //Destructor will free the memory if the value was an immediate.
    virtual~Instruction2Param(){
        if(!isRdAddress) delete rd;
        if(!isRsAddress) delete rs;
    };    //here the destructor of P is called so there is no need to do anything
};