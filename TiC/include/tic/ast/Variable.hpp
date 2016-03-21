#pragma once

#include <tic/ast/Node.hpp>
#include <tic/ast/VariableDeclaration.hpp>
#include <tic/ast/List.hpp>
#include <tic/SourceBlock.hpp>

namespace tic
{
namespace ast
{
class Variable : public Node
{
public:
    Variable(const std::string &varName);
    virtual ~Variable();
    
    const std::string& varName();
    
    VariableDeclaration* declaration();
    const VariableDeclaration* declaration() const;
    void setDeclaration(VariableDeclaration *declaration);
    
    void searchDeclaration(tic::ast::List::NodeList &nodes);
private:
    std::string m_varName;
    VariableDeclaration *m_declaration = nullptr;
};
}
}