#include<stdexcept>

class InsufficientParameters : public std::runtime_error
{
    public:
    explicit InsufficientParameters(const std::string& instruction):std::runtime_error("Insufficient parameters for "+ instruction ){};
};