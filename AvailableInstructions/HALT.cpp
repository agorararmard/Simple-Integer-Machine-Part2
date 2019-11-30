#include "../sizes.h"
#include "../Exceptions.h"
class haltInstruction: public Instruction{
    public:
    haltInstruction(){}
    virtual void exec(){
        throw HALTException(); //to be handled in main as breaking exception
    }
    ~haltInstruction(){};    //here the destructor of P is called so there is no need to do anything
};