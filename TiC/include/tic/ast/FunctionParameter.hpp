#pragma once

#include <tic/Type.hpp>
#include <tic/ast/Node.hpp>

namespace tic
{
namespace ast
{
class FunctionParameter : public Node
{
public:
    FunctionParameter(Type type, const std::string &varName);
    virtual ~FunctionParameter();
    
    const Type& type() const;
    const std::string& varName() const;
    
    void setType(const Type &type);
    void setVarName(const std::string &varName);
private:
    Type m_type;
    std::string m_varName;
};
}
}