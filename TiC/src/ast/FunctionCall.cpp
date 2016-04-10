#include <tic/ast/FunctionCall.hpp>
#include <tic/Error.hpp>
#include <tic/ErrorHandler.hpp>
#include <tic/ast/Variable.hpp>
#include <tic/ast/FunctionParameter.hpp>
#include <iostream>

using std::cout;
using std::endl;

namespace tic
{
namespace ast 
{
FunctionCall::FunctionCall(const std::string &functionName)
    : List("FunctionCall", NodeType::FunctionCall), m_functionName(functionName)
{

}
FunctionCall::~FunctionCall()
{

}
const std::string &FunctionCall::functionName() const
{
    return m_functionName;
}
Function *FunctionCall::declaration()
{
    return m_declaration;
}
List *FunctionCall::args()
{
    return &m_arguments;
}
void FunctionCall::pushArg(const std::string &varName, List &nodes)
{
    bool found = false;
    for(auto it = nodes.rbegin(); it != nodes.rend() && !found; ++it)
    {
        boost::shared_ptr<VariableDeclaration> declaration = boost::dynamic_pointer_cast<VariableDeclaration>(*it);
        if(declaration) {
            if(declaration->varName() == varName) {
                m_arguments.push_back(declaration);
                found = true;
            }
        }
    }
    
    if(nodes.type() == NodeType::Function || nodes.type() == NodeType::Program) {
        Function *func = static_cast<Function*>(&nodes);
        for(auto param : *(func->parameters()))
        {
            boost::shared_ptr<VariableDeclaration> declaration = boost::dynamic_pointer_cast<VariableDeclaration>(param);
            if(declaration) {
                if(declaration->varName() == varName) {
                    m_arguments.push_back(declaration);
                    found = true;
                }
            }
        }
    }
    
    if(!found) {
        errorHandler->handleError(Error("Function parameter \"" + varName + "\" of function \"" + functionName() + "\" is never declared!", debugInfo()));
    }
}
void FunctionCall::pushArg(std::unique_ptr< Number > number)
{
    m_arguments.push_back(std::move(number));
}
bool FunctionCall::searchDeclaration(List &nodes)
{
    bool found = false;
    for(auto it = nodes.rbegin(); it != nodes.rend() && !found; ++it)
    {
        boost::shared_ptr<Function> declaration = boost::dynamic_pointer_cast<Function>(*it);
        if(declaration) {
            if(declaration->functionName() == functionName()) {
                m_declaration = declaration.get();
                found = true;
            }
        }
    }
    return found;
}
}
}
