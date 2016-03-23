#pragma once

#include <tic/ast/Node.hpp>
#include <tic/Type.hpp>

namespace tic
{
namespace ast
{
class VariableDeclaration : public Node
{
public:
    VariableDeclaration(Type type, const std::string &varName);
    virtual ~VariableDeclaration();
    
    Type* type();
    const std::string& varName() const;
    
    void setVarName(const std::string &varName);
    void setType(const Type &type);
private:
    Type m_type;
    std::string m_varName;
};
}
}