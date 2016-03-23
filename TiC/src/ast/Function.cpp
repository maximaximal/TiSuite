#include <tic/ast/Function.hpp>
#include <tic/ast/FunctionParameter.hpp>
#include <tic/ast/VariableDeclaration.hpp>
#include <tic/ast/Variable.hpp>
#include <iostream>

using std::cout;
using std::endl;

namespace tic
{
namespace ast 
{
Function::Function(const std::string &functionName)
    : List("Function", NodeType::Function), m_functionName(functionName)
{
    
}
Function::~Function()
{

}
const std::string &Function::functionName() const
{
    return m_functionName;
}
void Function::loadFromTokens(SourceBlock::TokenVector &tokens, SourceBlock::TokenVector::iterator &current)
{
    tic::ast::List::loadFromTokens(tokens, current);
    
    bool end = false;
    
    // Parsing flags. 
    bool functionHead = true;
    bool parameterList = false;
    bool variableDeclarationInProgress = false;
    bool functionCall = false;
    
    for(auto it = current; it != tokens.end() && !end; ++it)
    {
        switch(it->first)
        {
            case TokenType::PARAM_LIST_BEGIN:
                if(functionHead) {
                    parameterList = true;
                }
                if(functionCall) {
                    
                }
                break;
            case TokenType::PARAM_LIST_END:
                parameterList = false;
                if(functionCall) {
                    functionCall = false;
                }
                break;
            case TokenType::SCOPE_BEGIN:
                if(functionHead) {
                    functionHead = false;
                }
                break;
            case TokenType::SCOPE_END:
                end = true;
                break;
            case TokenType::TYPE:
                if(parameterList) {
                    auto param = std::make_unique<FunctionParameter>(it->second, "");
                    param->setDebugInfo(it->toDebugInfo());
                    m_parameters.push_back(std::move(param));
                } else if(functionHead) {
                    // This has to be the function return type!
                    m_returnType = Type(it->second);
                } else {
                    auto decl = std::make_unique<VariableDeclaration>(it->second, "");
                    decl->setDebugInfo(it->toDebugInfo());
                    push_back(std::move(decl));
                }
                break;
            case TokenType::VAR_NAME:
                if(parameterList) {
                    boost::static_pointer_cast<FunctionParameter>(m_parameters.back())->setVarName(it->second);
                } else if(variableDeclarationInProgress) {
                    boost::static_pointer_cast<VariableDeclaration>(back())->setVarName(it->second);
                } else if(!functionHead) {
                    std::unique_ptr<Variable> var = std::make_unique<Variable>(it->second);
                    var->setDebugInfo(it->toDebugInfo());
                    //The declaration has to be searched!
                    var->searchDeclaration(*this);
                    push_back(std::move(var));
                }
                break;
            case TokenType::FUNCTION_CALL:
                functionCall = true;
                break;
        }
    }
}
List* Function::parameters() 
{
    return &m_parameters;
}
Type* Function::returnType()
{
    return &m_returnType;
}
}
}