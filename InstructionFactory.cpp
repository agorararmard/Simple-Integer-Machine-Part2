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

Instruction* InstructionFactory::createInstruction(std::string instType, std::string firstParam, std::string secondParam, std::string thirdParam,int&pc, int* &dataMemory, std::mutex* &ReadMutex, std::mutex* &WriteMutex, std::mutex* &memoryWrite){

    if(instType == "ADD"){

        if(firstParam!="" &&secondParam !="" && thirdParam !="")
        {
            int *p1,*p2,*p3;
            std::mutex *rdm;

            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            bool fp3 = interpretParam(thirdParam,p3,dataMemory);
            if(fp3){
                interpretMtx(thirdParam,rdm,memoryWrite);
            }
            return new addInstruction(*p1,fp1,*p2,fp2,*p3,fp3,*rdm);
        }
        else 
            throw InsufficientParameters("ADD");
    }
    
    if(instType =="NEG"){
        if(firstParam!="" &&secondParam !="" && thirdParam =="")
        {
            int *p1,*p2;
            std::mutex *rdm;
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            
            if(fp2){
                interpretMtx(secondParam,rdm,memoryWrite);
            }
            return new negInstruction(*p1,fp1,*p2,fp2,*rdm);
        }
        else 
            throw InsufficientParameters("NEG");
    }


    if(instType =="MUL"){
        if(firstParam!="" &&secondParam !="" && thirdParam !="")
        {
            int *p1,*p2,*p3;
            std::mutex *rdm;
            bool fp3 = interpretParam(thirdParam,p3,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            
            if(fp3){
                interpretMtx(thirdParam,rdm,memoryWrite);
            }
   
            return new mulInstruction(*p1,fp1,*p2,fp2,*p3,fp3,*rdm);
        }
        else 
            throw InsufficientParameters("MUL");
    }

    if(instType =="JMP"){

       if(firstParam!="" &&secondParam =="" && thirdParam =="")
        {
            int *p1;
            std::mutex *rdm;
            bool fp1 = interpretParam(firstParam,p1,dataMemory);

            return new jmpInstruction(*p1,fp1, pc,true,*rdm);
        }
        else 
            throw InsufficientParameters("JMP");
    }

    if(instType =="JMP0"){
       if(firstParam!="" &&secondParam !="" && thirdParam =="")
        {
            int *p1,*p2;
            std::mutex * rdm;

            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);

            return new jmp0Instruction(*p1,fp1,*p2,fp2,pc,true,*rdm);
        }
        else 
            throw InsufficientParameters("JMP0");
 
    }

    if(instType =="ASS"){
        if(firstParam!="" &&secondParam !="" && thirdParam =="")
        {
            int *p1,*p2;
            std::mutex *rdm;
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            
            if(fp2){
                interpretMtx(secondParam,rdm,memoryWrite);
            }
   
            return new assInstruction(*p1,fp1,*p2,fp2,*rdm);
        }
        else 
            throw InsufficientParameters("ASS");
    }

    if(instType =="LE"){
        if(firstParam!="" &&secondParam !="" && thirdParam !="")
        {
            int *p1,*p2,*p3;
            std::mutex *rdm;
            bool fp3 = interpretParam(thirdParam,p3,dataMemory);
            bool fp1 = interpretParam(firstParam,p1,dataMemory);
            bool fp2 = interpretParam(secondParam,p2,dataMemory);
            
            if(fp3){
                interpretMtx(thirdParam,rdm,memoryWrite);
            }
   
            return new leInstruction(*p1,fp1,*p2,fp2,*p3,fp3,*rdm);
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
            if(fp){
                interpretMtx(firstParam,rdm,memoryWrite);
            }
   
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
            if(fp){
                interpretMtx(firstParam,rdm,memoryWrite);
            }
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

