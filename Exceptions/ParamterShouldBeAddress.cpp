#include<stdexcept>
#include <string>
class ParamterShouldBeAddress : public std::runtime_error
{
    public:
    explicit ParamterShouldBeAddress(const std::string& instruction, const std::string& param):std::runtime_error("Paramter "+ param+" of instruction "+ instruction + " Should be address"){};
};
