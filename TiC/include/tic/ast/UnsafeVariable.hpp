#pragma once

#include <tic/ast/Node.hpp>
#include <tic/Type.hpp>

namespace tic
{
namespace ast 
{
class UnsafeVariable : public Node
{
public:
    UnsafeVariable(Type type, const std::string &variable);
    virtual ~UnsafeVariable();
    
    const std::string& variable();
    void setVariable(const std::string &variable);
    
    Type* type();
    void setType(const Type &type);
private:
    std::string m_variable;
    Type m_type;
};
}
}