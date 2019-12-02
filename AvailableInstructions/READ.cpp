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
           std::unique_lock<std::mutex>  lck1 {*rdm, std::defer_lock};
           std::unique_lock<std::mutex>  lck2 {*opm, std::defer_lock};
         
        lock(lck1,lck2);
        std::cin >> *rs;

    }
    ~readInstruction(){}
};