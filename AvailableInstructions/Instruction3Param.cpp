#include"../sizes.h"
class Instruction3Param: public Instruction{
    protected:
        int *rd;    //rd is always an address
        int *rs1;
        int *rs2;
        bool isRdAddress;
        bool isRs1Address;
        bool isRs2Address;
    public:
    
    Instruction3Param(int& rs1, bool isRs1Address,int& rs2, bool isRs2Address,int& rd, bool isRdAddress):rd(&rd),isRdAddress(isRdAddress),rs1(&rs1),isRs1Address(isRs1Address),rs2(&rs2),isRs2Address(isRs2Address){

    }
    
    virtual void exec()=0;

    //Destructor will free the memory if the value was an immediate.
    virtual ~Instruction3Param(){
        if(!isRdAddress) delete rd;
        if(!isRs1Address) delete rs1;
        if(!isRs2Address) delete rs2;
    };  
};