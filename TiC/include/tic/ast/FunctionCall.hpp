#pragma once

#include <boost/container/vector.hpp>
#include <boost/shared_ptr.hpp>
#include <tic/ast/List.hpp>
#include <tic/ast/Function.hpp>
#include <tic/ast/Variable.hpp>
#include <tic/ast/Number.hpp>

namespace tic
{
namespace ast
{
/**
 * Describes a function call. The node list contains variable nodes to pass to the function.
 */
class FunctionCall : public List
{
public:
    FunctionCall(const std::string &functionName);
    virtual ~FunctionCall();
    
    Function* declaration();
    List* args();
    
    // Pushes an argument to the function and searches the variable node. 
    void pushArg(const std::string &varName, tic::ast::List &nodes);
    void pushArg(std::unique_ptr<ast::Number> number);
    
    bool searchDeclaration(tic::ast::List &nodes);
    
    const std::string& functionName() const;
private:
    List m_arguments;
    std::string m_functionName;
    Function *m_declaration = nullptr;
};
}
}
