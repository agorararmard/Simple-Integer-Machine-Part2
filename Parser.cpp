#include "Parser.h"
 
void Parser::getInstructionType(std::string& line,std::string& instType){
    std::size_t pos = line.find(" ");
    
    instType = line.substr(0,pos);
}

void Parser::getFirstParameter(std::string& line,std::string& firstParam){
    std::size_t pos1 = line.find(" ");
    std::size_t pos2 = line.find(",");
    
    if(pos1 != std::string::npos)
        firstParam = line.substr(pos1+1,pos2-pos1-1);
    else
        firstParam = "";
    
}

void Parser::getSecondParameter(std::string& line,std::string& secondParam){
    std::size_t pos1 = line.find(",");
    std::size_t pos2 = line.rfind(",");
    if(pos1 != std::string::npos)
        secondParam = line.substr(pos1+1,pos2-pos1-1);
    else
        secondParam ="";
}

void Parser::getThirdParameter(std::string& line,std::string& thirdParam){
    std::size_t pos1 = line.rfind(",");
    std::size_t pos2 = line.length();
   
    if(pos1 == line.find(","))
        {
            thirdParam = "";
            return;
        }

    if(pos1 != std::string::npos)
        thirdParam = line.substr(pos1+1,pos2-pos1-1);
    else
        thirdParam = "";
}




void Parser::readInstMem(){
    std::ifstream fin;
    fin.open(fileInst);

    if(!fin.good()) 
        throw BadFile();

    std::string line;
    int inc = 0;
    
    std::string instType;
    std::string firstParam;
    std::string secondParam;
    std::string thirdParam;
        
    while(getline(fin, line), !fin.eof()){
        
        getInstructionType(line, instType);
        getFirstParameter(line, firstParam);
        getSecondParameter(line, secondParam);
        getThirdParameter(line, thirdParam);
        instMemory[inc] = instFactory.createInstruction(instType,firstParam,secondParam,thirdParam,*pc,dataMemory);
        inc++;
    }    
    fin.close();
}