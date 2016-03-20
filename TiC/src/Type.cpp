#include <tic/Type.hpp>

namespace tic
{
Type::Type()
{

}
Type::~Type()
{

}
bool Type::isType(const std::string &str)
{
    if(str == "num") {
        return true;
    } else if(str == "lst") {
        return true;
    } else if(str == "mat") {
        return true;
    } else if(str == "str") {
        return true;
    }
    return false;
}
}