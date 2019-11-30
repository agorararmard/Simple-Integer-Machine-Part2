#include<stdexcept>
#include <string>
class InvalidInstruction : public std::runtime_error
{
    public:
    explicit InvalidInstruction(const std::string& instruction):std::runtime_error("Invalid instruction "+ instruction){};
};
