#include <tic/ast/VariableDeclaration.hpp>

namespace tic 
{
namespace ast 
{
VariableDeclaration::VariableDeclaration(Type type, const std::string &varName, const std::string &nodeName, NodeType nodeType)
    : Node(nodeName, nodeType), m_type(type), m_varName(varName)
{

}
VariableDeclaration::~VariableDeclaration()
{

}
Type *VariableDeclaration::type()
{
    return &m_type;
}
const std::string &VariableDeclaration::varName() const
{
    return m_varName;
}
void VariableDeclaration::setType(const Type &type)
{
    m_type = type;
}
void VariableDeclaration::setVarName(const std::string &varName)
{
    m_varName = varName;
}
}
}
