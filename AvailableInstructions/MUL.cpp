#include"../sizes.h"
#include"../Exceptions.h"
class mulInstruction: public Instruction3Param{
    public:
    mulInstruction(int& rs1, bool isRs1Address,int& rs2, bool isRs2Address,int& rd, bool isRdAddress,std::mutex &rdm1,std::mutex &rdm2,std::mutex &rdm3): Instruction3Param(rs1, isRs1Address, rs2, isRs2Address, rd, isRdAddress,rdm1,rdm2,rdm3){
        if(!isRdAddress){
                throw ParamterShouldBeAddress("MUL", "3");
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

        int tmp1 = *rs1;
        int tmp2 = *rs2;

   //     if(isRdAddress) rdm1->lock();
        *rd = (*rs1) * (*rs2);
 //       if(isRdAddress) rdm1->unlock();
        int tmp3 = *rd;
     
     if(rdm2 != nullptr){
            delete lck1; 
            delete lck2; 
            if(rdm3 != nullptr){   
                delete lck3;
            }
        }else{
            rdm1->unlock();
        }

        if(tmp1 !=0 && tmp2!=0){    //for detecting overflow
            if(tmp3/ tmp1 != tmp2){
                throw OverFlow();
            }
        }
    }
    ~mulInstruction(){}
};