#include<stdexcept>

class OutOfDataMemoryBounds : public std::runtime_error
{
    public:
    explicit OutOfDataMemoryBounds():std::runtime_error("Out of data memory bounds"){};
};