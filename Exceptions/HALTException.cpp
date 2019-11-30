#include<stdexcept>

class HALTException : public std::runtime_error
{
    public:
    explicit HALTException():std::runtime_error("End of Program"){};
};