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
Type::Type(Type::TypeEnum type)
    : m_type(type)
{

}
Type::~Type()
{

}
Type::TypeEnum Type::type() const
{
    return m_type;
}
void Type::setType(Type::TypeEnum type)
{
    m_type = type;
}
std::string Type::toStringStatic(const tic::Type *type)
{
    switch(type->type()) 
    {
        case NUMBER:
            return "num";
        case LIST:
            return "lst";
        case STRING:
            return "str";
        case MATRIX:
            return "mat";
        case UNKNOWN:
            return "unknown";
        case NO_TYPE:
            return "no_type";
    }
}
std::string Type::toString() 
{
    return Type::toStringStatic(this);
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