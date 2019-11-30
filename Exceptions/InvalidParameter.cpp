#include<stdexcept>
#include <string>
class InvalidParameter : public std::runtime_error
{
    public:
    explicit InvalidParameter(const std::string& parameter):std::runtime_error("Invalid parameter "+ parameter){};
};
