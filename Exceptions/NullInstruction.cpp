#include<stdexcept>

class NullInstruction : public std::runtime_error
{
    public:
    explicit NullInstruction():std::runtime_error("Jumped to a position that doesn't have a defined instruction"){};
};
