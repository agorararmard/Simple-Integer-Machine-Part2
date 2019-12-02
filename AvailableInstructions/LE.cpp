#include"../sizes.h"
#include"../Exceptions.h"
class leInstruction: public Instruction3Param{
    public:
    leInstruction(int& rs1, bool isRs1Address,int& rs2, bool isRs2Address,int& rd, bool isRdAddress ,std::mutex &rdm1,std::mutex &rdm2,std::mutex &rdm3): Instruction3Param(rs1, isRs1Address, rs2, isRs2Address, rd, isRdAddress,rdm1,rdm2,rdm3){
        if(!isRdAddress){
            throw ParamterShouldBeAddress("LE", "3");
        }
    }
    virtual void exec(){
        std::unique_lock<std::mutex> *lck1,*lck2,*lck3;
        if(rdm2 != nullptr){
            lck1 = new std::unique_lock<std::mutex>{*rdm1, std::defer_lock};
            lck2 = new std::unique_lock<std::mutex>{*rdm2, std::defer_lock};
            if(rdm3 == nullptr){   
               std::lock(*lck1,*lck2);
            }else{
                lck3 = new std::unique_lock<std::mutex>{*rdm3, std::defer_lock};
                std::lock(*lck1,*lck2,*lck3);
            }
        }else{
            rdm1->lock();
        }

        //if(isRdAddress) rdm1->lock();
        *rd = (*rs1 <=*rs2)? 1:0;
        //if(isRdAddress) rdm1->unlock();
            if(rdm2 != nullptr){
            delete lck1; 
            delete lck2; 
            if(rdm3 != nullptr){   
                delete lck3;
            }
        }else{
            rdm1->unlock();
        }
   
    }
    ~leInstruction(){}
};