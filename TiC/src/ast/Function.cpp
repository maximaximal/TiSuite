#include <tic/ast/Function.hpp>
#include <tic/ast/FunctionParameter.hpp>
#include <tic/ast/FunctionCall.hpp>
#include <tic/ast/VariableDeclaration.hpp>
#include <tic/ast/Variable.hpp>
#include <tic/ast/Command.hpp>
#include <tic/ast/Scope.hpp>
#include <tic/Token.hpp>
#include <iostream>

using std::cout;
using std::endl;

namespace tic
{
namespace ast 
{
Function::Function(const std::string &functionName, const char *nodeName, tic::ast::NodeType nodeType)
    : Scope(nodeName, nodeType), m_functionName(functionName)
{
    
}
Function::~Function()
{

}
const std::string &Function::functionName() const
{
    return m_functionName;
}
void Function::loadFromTokens(SourceBlock::TokenVector &tokens, SourceBlock::TokenVector::iterator &current, List &rootList)
{
    bool end = false;
    
    // Parsing flags. 
    bool functionHead = true;
    bool parameterList = true;
    
    bool handledByScope = false;
    
    for(auto it = current; it != tokens.end() && !end; ++it)
    {
        if(handledByScope) {
            end = Scope::parseToken(tokens, it, rootList);
        } else {
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
                {
                    functionHead = false;
                    handledByScope = true;
                    break;
                }
                case TokenType::SCOPE_END:
                    end = true;
                    break;
                case TokenType::TYPE:
                {
                    if(parameterList) {
                        auto param = std::make_unique<FunctionParameter>(it->second, "");
                        param->setDebugInfo(it->toDebugInfo());
                        m_parameters.push_back(std::move(param));
                    }
                    break;
                }
                case TokenType::VAR_NAME:
                {
                    if(parameterList) {
                        boost::static_pointer_cast<FunctionParameter>(m_parameters.back())->setVarName(it->second);
                    } 
                    break;
                }
                case TokenType::NUMBER:
                    break;
                case TokenType::FUNCTION_CALL:
                    break;
                case TokenType::COMMAND:
                {
                    auto cmd = std::make_unique<Command>(it->second);
                    cmd->setDebugInfo(it->toDebugInfo());
                    push_back(std::move(cmd));
                    break;
                }
            }
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
