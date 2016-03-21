#include <tic/ast/FunctionParameter.hpp>

namespace tic
{
namespace ast
{
FunctionParameter::FunctionParameter(Type type, const std::string &varName)
    : Node("FunctionParameter"), m_type(type), m_varName(varName)
{

}
FunctionParameter::~FunctionParameter()
{

}
Type FunctionParameter::type() const
{
    return m_type;
}
const std::string &FunctionParameter::varName() const
{
    return m_varName;
}
void FunctionParameter::setType(Type type)
{
    m_type = type;
}
void FunctionParameter::setVarName(const std::string &varName)
{
    m_varName = varName;
}
}
}