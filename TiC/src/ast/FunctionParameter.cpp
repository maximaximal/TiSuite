#include <tic/ast/FunctionParameter.hpp>

namespace tic
{
namespace ast
{
FunctionParameter::FunctionParameter(Type type, const std::string &varName)
    : Node("FunctionParameter", NodeType::FunctionParameter), m_type(type), m_varName(varName)
{

}
FunctionParameter::~FunctionParameter()
{

}
const Type& FunctionParameter::type() const
{
    return m_type;
}
const std::string &FunctionParameter::varName() const
{
    return m_varName;
}
const std::string &FunctionParameter::assignedVarName() const
{
    return m_assignedVarName;
}
void FunctionParameter::setType(const Type &type)
{
    m_type = type;
}
void FunctionParameter::setVarName(const std::string &varName)
{
    m_varName = varName;
}
void FunctionParameter::setAssignedVarName(const std::string &varName)
{
    m_assignedVarName = varName;
}
}
}