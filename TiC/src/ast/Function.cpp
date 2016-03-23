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
    : List("Function", NodeType::Function)
{
    
}
Function::~Function()
{

}
const std::string &Function::functionName() const
{

}
void Function::loadFromTokens(SourceBlock::TokenVector &tokens, SourceBlock::TokenVector::iterator &current)
{
    tic::ast::List::loadFromTokens(tokens, current);
    
    bool end = false;
    
    // Parsing flags. 
    bool functionHead = true;
    bool parameterList = false;
    bool variableDeclarationInProgress = false;
    
    for(auto it = current; it != tokens.end() && !end; ++it)
    {
        switch(it->first)
        {
            case TokenType::PARAM_LIST_BEGIN:
                if(functionHead) {
                    parameterList = true;
                }
                break;
            case TokenType::PARAM_LIST_END:
                parameterList = false;
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
                    m_parameters.push_back(std::move(std::make_unique<FunctionParameter>(it->second, "")));
                } else if(functionHead) {
                    // This has to be the function return type!
                    m_returnType = Type(it->second);
                } else {
                    push_back(std::move(std::make_unique<VariableDeclaration>(it->second, "")));
                }
                break;
            case TokenType::VAR_NAME:
                if(parameterList) {
                    std::static_pointer_cast<FunctionParameter>(m_parameters.back())->setVarName(it->second);
                } else if(variableDeclarationInProgress) {
                    std::static_pointer_cast<VariableDeclaration>(back())->setVarName(it->second);
                } else if(!functionHead) {
                    std::unique_ptr<Variable> var = std::make_unique<Variable>(it->second);
                    //The declaration has to be searched!
                    var->searchDeclaration(*this);
                    push_back(std::move(var));
                }
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