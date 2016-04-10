#pragma once

#include <tic/Type.hpp>
#include <tic/ast/VariableDeclaration.hpp>

namespace tic
{
namespace ast
{
class FunctionParameter : public VariableDeclaration
{
public:
    FunctionParameter(Type type, const std::string &varName);
    virtual ~FunctionParameter();
    
    const std::string& assignedVarName() const;
    
    void setAssignedVarName(const std::string &varName);
private:
    std::string m_assignedVarName;
};
}
}
