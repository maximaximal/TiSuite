#include <tic/Type.hpp>

namespace tic
{
Type::Type()
{

}
Type::Type(const std::string &typeString)
{
    if(typeString == "num") {
        m_type = NUMBER;
    } else if(typeString == "lst") {
        m_type = LIST;
    } else if(typeString == "mat") {
        m_type = MATRIX;
    } else if(typeString == "str") {
        m_type = STRING;
    }
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