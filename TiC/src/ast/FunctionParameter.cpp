#include <tic/ast/FunctionParameter.hpp>

namespace tic
{
namespace ast
{
FunctionParameter::FunctionParameter(Type type, const std::string &varName)
    : tic::ast::VariableDeclaration(type, varName, "FunctionParameter", NodeType::FunctionParameter)
{

}
FunctionParameter::~FunctionParameter()
{

}
const std::string &FunctionParameter::assignedVarName() const
{
    return m_assignedVarName;
}
void FunctionParameter::setAssignedVarName(const std::string &varName)
{
    m_assignedVarName = varName;
}
}
}
