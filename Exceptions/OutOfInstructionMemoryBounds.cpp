#include<stdexcept>

class OutOfInstructionMemoryBounds : public std::runtime_error
{
    public:
    explicit OutOfInstructionMemoryBounds():std::runtime_error("Out of instruction memory bounds"){};
};