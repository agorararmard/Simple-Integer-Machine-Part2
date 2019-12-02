#include"../sizes.h"
#include"../Exceptions.h"
class negInstruction: public Instruction2Param{
    public:
    negInstruction(int& rs, bool isRsAddress,int& rd, bool isRdAddress,std::mutex &rdm1,std::mutex &rdm2): Instruction2Param(rs, isRsAddress, rd, isRdAddress,rdm1,rdm2){
        if(!isRdAddress){
                throw ParamterShouldBeAddress("NEG", "2");
        }
    }
    virtual void exec(){
                std::unique_lock<std::mutex> *lck1,*lck2;
        if(rdm2 != nullptr){
            lck1 = new std::unique_lock<std::mutex>{*rdm1, std::defer_lock};
            lck2 = new std::unique_lock<std::mutex>{*rdm2, std::defer_lock};
            std::lock(*lck1,*lck2);
        }else{
            rdm1->lock();
        }
       // if(isRdAddress) rdm1->lock();
        *rd = -(*rs);
     //   if(isRdAddress) rdm1->unlock();
         if(rdm2 != nullptr){
            delete lck1; 
            delete lck2; 
        }else{
            rdm1->unlock();
        }
    }
    ~negInstruction(){}
};