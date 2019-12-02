#include "InstructionFactory.h"

int InstructionFactory::convertToInt(std::string s){
    int ret = atoi(s.c_str());
    if(!ret && !(s[0] == '0' && s.length()==1)) throw InvalidParameter(s);
    return ret;
}
bool InstructionFactory::interpretParam(std::string &param,int* &p, int* &dataMemory){
            if(param[0] == '$'){
                int address = convertToInt(param.substr(1));
                if(address >=0 && address < dataMemorySize)
                    {
                        p = &dataMemory[address];
                        return true;
                    }
                    else throw OutOfDataMemoryBounds();
            }else {
                p = new int;
                *p = convertToInt(param); 
            }
            return false;
}
void InstructionFactory::interpretMtx(std::string &param,std::mutex* &mtx, std::mutex* &memoryWrite, int& idx){
            if(param[0] == '$'){
                int address = convertToInt(param.substr(1));
                if(address >=0 && address < dataMemorySize)
                    {
                        mtx = &memoryWrite[address];
                        idx = address;
                    }
                    else throw OutOfDataMemoryBounds();
            }else {
                mtx = nullptr; 
                idx = -1;
            }
}

void InstructionFactory::sortMtxs(std::mutex* &mtx1,std::mutex* &mtx2,std::mutex* &mtx3, int idx1,int idx2, int idx3){
    int tmpi;
    std::mutex* tmpm;
    if(idx1 == idx2 && idx1 != -1){
        idx2 = -1;
        mtx2 = nullptr;

    }
    if(idx1 == idx3 && idx1 != -1){
        idx3 = -1;
        mtx3 = nullptr;
    }

    if(idx3 == idx2 && idx3 != -1){
        idx2 = -1;
        mtx2 = nullptr;
    }

    if(idx1 > idx2){
        tmpi= idx1;
        idx1 = idx2;
        idx2 = tmpi;

        tmpm= mtx1;
        mtx1 = mtx2;
        mtx2 = tmpm;
    }
    if(idx1 > idx3){
        tmpi= idx1;
        idx1 = idx3;
        idx3 = tmpi;
        
        tmpm= mtx1;
        mtx1 = mtx3;
        mtx3 = tmpm;
    }
    if(idx2 > idx3){
        tmpi= idx3;
        idx3 = idx2;
        idx2 = tmpi;
        
        tmpm= mtx3;
        mtx3 = mtx2;
        mtx2 = tmpm;
    }
}
void InstructionFactory::sortMtxs(std::mutex* &mtx1,std::mutex* &mtx2, int idx1, int idx2){
    int tmpi;
    std::mutex* tmpm;
    if(idx1 == idx2 && idx1 != -1){
        idx2 = -1;
        mtx2 = nullptr;
        return;
    }
    if(idx1 > idx2){
        tmpi= idx1;
        idx1 = idx2;
        idx2 = tmpi;

        tmpm= mtx1;
        mtx1 = mtx2;
        mtx2 = tmpm;
    }
}
Instruction* InstructionFactory::createInstruction(std::string instType, std::string firstParam, std::string secondParam, std::string thirdParam,int&pc, int* &dataMemory, std::mutex* &ReadMutex, std::mutex* &WriteMutex, std::mutex* &memoryWrite){

    if(instType == "ADD"){

        if(firstParam!="" &&secondParam !="" && thirdParam !="")
        {
            int *p1,*p2,*p3;
            std::mutex *rdm1,*rdm2,*rdm3;
            int idx1,idx2,idx3;
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            bool fp3 = interpretParam(thirdParam,p3,dataMemory);
            interpretMtx(firstParam,rdm1,memoryWrite,idx1);
            interpretMtx(secondParam,rdm2,memoryWrite, idx2);
            interpretMtx(thirdParam,rdm3,memoryWrite, idx3);
            sortMtxs(rdm1,rdm2,rdm3,idx1,idx2,idx3);

            return new addInstruction(*p1,fp1,*p2,fp2,*p3,fp3,*rdm1,*rdm2,*rdm3);
        }
        else 
            throw InsufficientParameters("ADD");
    }
    
    if(instType =="NEG"){
        if(firstParam!="" &&secondParam !="" && thirdParam =="")
        {
            int *p1,*p2;
            std::mutex *rdm1,*rdm2;
            int idx1,idx2;
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            
            interpretMtx(firstParam,rdm1,memoryWrite,idx1);
            interpretMtx(secondParam,rdm2,memoryWrite, idx2);
            sortMtxs(rdm1,rdm2, idx1,idx2);
            
            return new negInstruction(*p1,fp1,*p2,fp2,*rdm1,*rdm2);
        }
        else 
            throw InsufficientParameters("NEG");
    }


    if(instType =="MUL"){
        if(firstParam!="" &&secondParam !="" && thirdParam !="")
        {
            int *p1,*p2,*p3;
            std::mutex *rdm1,*rdm2,*rdm3;
            int idx1,idx2,idx3;
            bool fp3 = interpretParam(thirdParam,p3,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            
            interpretMtx(firstParam,rdm1,memoryWrite,idx1);
            interpretMtx(secondParam,rdm2,memoryWrite,idx2);
            interpretMtx(thirdParam,rdm3,memoryWrite, idx3);
            sortMtxs(rdm1,rdm2,rdm3, idx1,idx2,idx3);         
   
            return new mulInstruction(*p1,fp1,*p2,fp2,*p3,fp3,*rdm1,*rdm2,*rdm3);
        }
        else 
            throw InsufficientParameters("MUL");
    }

    if(instType =="JMP"){

       if(firstParam!="" &&secondParam =="" && thirdParam =="")
        {
            int *p1;
            std::mutex *rdm1, *rdm2;
            int idx1;
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            interpretMtx(firstParam,rdm1,memoryWrite,idx1);
            rdm2 = nullptr;
            return new jmpInstruction(*p1,fp1, pc,true,*rdm1,*rdm2);
        }
        else 
            throw InsufficientParameters("JMP");
    }

    if(instType =="JMP0"){
       if(firstParam!="" &&secondParam !="" && thirdParam =="")
        {
            int *p1,*p2;
            std::mutex *rdm1,*rdm2,*rdm3;
            int idx1, idx2;
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);

            interpretMtx(firstParam,rdm1,memoryWrite,idx1);
            interpretMtx(secondParam,rdm2,memoryWrite,idx2);
            sortMtxs(rdm1,rdm2,idx1,idx2);
            rdm3 = nullptr;

            return new jmp0Instruction(*p1,fp1,*p2,fp2,pc,true,*rdm1,*rdm2,*rdm3);
        }
        else 
            throw InsufficientParameters("JMP0");
 
    }

    if(instType =="ASS"){
        if(firstParam!="" &&secondParam !="" && thirdParam =="")
        {
            int *p1,*p2;
            std::mutex *rdm1,*rdm2;
            int idx1,idx2;
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            
            
            interpretMtx(firstParam,rdm1,memoryWrite,idx1);
            interpretMtx(secondParam,rdm2,memoryWrite,idx2);
            sortMtxs(rdm1,rdm2, idx1,idx2);
   
            return new assInstruction(*p1,fp1,*p2,fp2,*rdm1,*rdm2);
        }
        else 
            throw InsufficientParameters("ASS");
    }

    if(instType =="LE"){
        if(firstParam!="" &&secondParam !="" && thirdParam !="")
        {
            int *p1,*p2,*p3;
            std::mutex *rdm1,*rdm2,*rdm3;
            int idx1,idx2,idx3;
            bool fp3 = interpretParam(thirdParam,p3,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            interpretMtx(firstParam,rdm1,memoryWrite,idx1);
            interpretMtx(secondParam,rdm2,memoryWrite,idx2);
            interpretMtx(thirdParam,rdm3,memoryWrite, idx3);
            sortMtxs(rdm1,rdm2,rdm3,idx1,idx2,idx3);

   
            return new leInstruction(*p1,fp1,*p2,fp2,*p3,fp3,*rdm1,*rdm2,*rdm3);
        }
        else 
            throw InsufficientParameters("LE");
    }

    if(instType =="READ"){

        if(firstParam!="" &&secondParam =="" && thirdParam =="")
        {

            int *p;
            std::mutex * rdm;
            int idx;
            bool fp = interpretParam(firstParam,p,dataMemory);
            interpretMtx(firstParam,rdm,memoryWrite, idx);
            
            return new readInstruction(*p,fp,*rdm,*ReadMutex);
        }
        else 
            throw InsufficientParameters("READ");
    }

    if(instType =="WRITE"){
        if(firstParam!="" &&secondParam =="" && thirdParam =="")
        {
            int *p;
            std::mutex * rdm;
            int idx;
            bool fp = interpretParam(firstParam,p,dataMemory);
            interpretMtx(firstParam,rdm,memoryWrite, idx);
            
            return new writeInstruction(*p,fp,*rdm,*WriteMutex);
        }
        else 
            throw InsufficientParameters("WRITE");
        
    }


    if(instType =="HALT"){
        if(firstParam =="" && secondParam =="" && thirdParam =="")
            return new haltInstruction();
        else{
            throw InsufficientParameters("HALT");
        }
    }


    
    throw InvalidInstruction(instType);
}

