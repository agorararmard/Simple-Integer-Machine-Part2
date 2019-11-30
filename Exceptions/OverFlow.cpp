#include<stdexcept>

class OverFlow : public std::runtime_error
{
    public:
    explicit OverFlow():std::runtime_error("Overflow occured"){};
};