class Instruction{
    public:
    Instruction(){}
    virtual void exec()=0;
    virtual ~Instruction(){};    //here the destructor of P is called so there is no need to do anything
};

