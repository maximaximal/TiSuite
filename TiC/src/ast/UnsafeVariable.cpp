#include <tic/ast/UnsafeVariable.hpp>

namespace tic
{
namespace ast 
{
UnsafeVariable::UnsafeVariable(Type type, const std::string &variable)
    : Node("UnsafeVariable", NodeType::UnsafeVariable), m_type(type), m_variable(variable)
{

}
UnsafeVariable::~UnsafeVariable()
{

}
const std::string &UnsafeVariable::variable()
{
    return m_variable;
}
void UnsafeVariable::setVariable(const std::string &variable)
{
    m_variable = variable;
}
Type* UnsafeVariable::type()
{
    return &m_type;
}
void UnsafeVariable::setType(const Type &type)
{
    m_type = type;
}

}
}