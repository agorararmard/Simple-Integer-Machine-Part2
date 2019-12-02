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
void InstructionFactory::interpretMtx(std::string &param,std::mutex* &mtx, std::mutex* &memoryWrite){
            if(param[0] == '$'){
                int address = convertToInt(param.substr(1));
                if(address >=0 && address < dataMemorySize)
                    {
                        mtx = &memoryWrite[address];
                    }
                    else throw OutOfDataMemoryBounds();
            }else {
                mtx = nullptr; 
            }
}

void InstructionFactory::sortMtxs(std::mutex* &mtx1,std::mutex* &mtx2,std::mutex* &mtx3){
    if(mtx1 == nullptr){
        if(mtx3 == nullptr){
            mtx1 = mtx2;
        }else{
            mtx1 = mtx3;
        }
    }else if (mtx2 == nullptr){
        mtx2 = mtx3;
    }
}
void InstructionFactory::sortMtxs(std::mutex* &mtx1,std::mutex* &mtx2){
    if(mtx1 == nullptr){
            mtx1 = mtx2;
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
            interpretMtx(firstParam,rdm1,memoryWrite);
            interpretMtx(secondParam,rdm2,memoryWrite);
            interpretMtx(thirdParam,rdm3,memoryWrite);
            sortMtxs(rdm1,rdm2,rdm3);

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
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            
            interpretMtx(firstParam,rdm1,memoryWrite);
            interpretMtx(secondParam,rdm2,memoryWrite);
            sortMtxs(rdm1,rdm2);
            
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
            bool fp3 = interpretParam(thirdParam,p3,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            
            interpretMtx(firstParam,rdm1,memoryWrite);
            interpretMtx(secondParam,rdm2,memoryWrite);
            interpretMtx(thirdParam,rdm3,memoryWrite);
            sortMtxs(rdm1,rdm2,rdm3);         
   
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
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
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

            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);

            interpretMtx(firstParam,rdm1,memoryWrite);
            interpretMtx(secondParam,rdm2,memoryWrite);
            sortMtxs(rdm1,rdm2);
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
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            
            
            interpretMtx(firstParam,rdm1,memoryWrite);
            interpretMtx(secondParam,rdm2,memoryWrite);
            sortMtxs(rdm1,rdm2);
   
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
            bool fp3 = interpretParam(thirdParam,p3,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            interpretMtx(firstParam,rdm1,memoryWrite);
            interpretMtx(secondParam,rdm2,memoryWrite);
            interpretMtx(thirdParam,rdm3,memoryWrite);
            sortMtxs(rdm1,rdm2,rdm3);

   
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
            bool fp = interpretParam(firstParam,p,dataMemory);
            interpretMtx(firstParam,rdm,memoryWrite);
            
   
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
            bool fp = interpretParam(firstParam,p,dataMemory);
            interpretMtx(firstParam,rdm,memoryWrite);
            
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

