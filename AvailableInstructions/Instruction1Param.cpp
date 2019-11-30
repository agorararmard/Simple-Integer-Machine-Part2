#include "../sizes.h"
class Instruction1Param: public Instruction{
    protected:
        int *rs;
        bool isRsAddress;
    public:
    Instruction1Param(int& rs, bool isRsAddress):rs(&rs),isRsAddress(isRsAddress){

    }
    virtual void exec()=0;

    //Destructor will free the memory if the value was an immediate.
    virtual ~Instruction1Param(){
        if(!isRsAddress) delete rs;
    };    //here the destructor of P is called so there is no need to do anything
};