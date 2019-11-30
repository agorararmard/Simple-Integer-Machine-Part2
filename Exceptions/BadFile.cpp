#include<stdexcept>

class BadFile : public std::runtime_error
{
    public:
    explicit BadFile():std::runtime_error("File is corrupt or unavailable. Please check the name of the file"){};
};