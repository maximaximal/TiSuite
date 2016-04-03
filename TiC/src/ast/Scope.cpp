#include <tic/ast/Scope.hpp>
#include <tic/ast/FunctionCall.hpp>
#include <tic/ast/Variable.hpp>
#include <tic/ast/VariableDeclaration.hpp>
#include <tic/ast/Command.hpp>
#include <iostream>

using std::endl;
using std::cout;

namespace tic
{
namespace ast
{
Scope::Scope(const char *nodeName, NodeType nodeType)
    : List(nodeName, nodeType)
{

}
Scope::~Scope()
{

}
void Scope::loadFromTokens(SourceBlock::TokenVector &tokens, SourceBlock::TokenVector::iterator &current, List &rootList)
{
    tic::ast::List::loadFromTokens(tokens, current);
    
    bool end = false;
    
    
    for(auto it = current; it != tokens.end() && !end; ++it)
    {
        end = parseToken(tokens, current, rootList);
    }
}
bool Scope::parseToken(SourceBlock::TokenVector &tokens, SourceBlock::TokenVector::iterator &it, List &rootList)
{
    switch(it->first)
    {
        case TokenType::PARAM_LIST_BEGIN:
            if(functionCall) {
                // Nothing to do at this stage. 
            } 
            if(command) {
                auto cmd = std::make_unique<Command>(it->second);
                cmd->setDebugInfo(it->toDebugInfo());
                push_back(std::move(cmd));
            }
            break;
        case TokenType::PARAM_LIST_END:
            if(functionCall) {
                functionCall = false;
            } 
            if(command) {
                auto cmd = std::make_unique<Command>(it->second);
                cmd->setDebugInfo(it->toDebugInfo());
                push_back(std::move(cmd));
            }
            break;
        case TokenType::VAR_SCOPE_BEGIN:
        {
            if(command) {
                auto cmd = std::make_unique<Command>(it->second);
                cmd->setDebugInfo(it->toDebugInfo());
                push_back(std::move(cmd));
            }
            break;
        }
        case TokenType::VAR_SCOPE_END:
        {
            if(command) {
                auto cmd = std::make_unique<Command>(it->second);
                cmd->setDebugInfo(it->toDebugInfo());
                push_back(std::move(cmd));
            }
            break;
        }
        case TokenType::END_STATEMENT:
            if(command) {
                command = false;
            }
            break;
        case TokenType::SCOPE_BEGIN:
        {
            // Do nothing
            /*
            //Another scope starts!
            auto scope = std::make_unique<Scope>();
            scope->setDebugInfo(it->toDebugInfo());
            scope->loadFromTokens(tokens, ++it, rootList);
            push_back(std::move(scope));
            // The iterator has been increased by the child scope, so this doesn't need to do anything else. 
            break;
            */
            if(command) {
                auto cmd = std::make_unique<Command>(it->second);
                cmd->setDebugInfo(it->toDebugInfo());
                push_back(std::move(cmd));
            }
            break;
        }
        case TokenType::SCOPE_END:
            if(command) {
                auto cmd = std::make_unique<Command>(it->second);
                cmd->setDebugInfo(it->toDebugInfo());
                push_back(std::move(cmd));
            }
            return true;
            break;
        case TokenType::TYPE:
        {
            if(command) {
                auto cmd = std::make_unique<Command>(it->second);
                cmd->setDebugInfo(it->toDebugInfo());
                push_back(std::move(cmd));
            } else {
                //A type has to be a variable declaration in a scope. 
                auto decl = std::make_unique<VariableDeclaration>(it->second, "");
                decl->setDebugInfo(it->toDebugInfo());
                push_back(std::move(decl));
                variableDeclarationInProgress = true;
            }
            break;
        }
        case TokenType::VAR_NAME:
        {
            if(variableDeclarationInProgress) {
                boost::static_pointer_cast<VariableDeclaration>(back())->setVarName(it->second);
                variableDeclarationInProgress = false;
            } else if(functionCall) {
                boost::static_pointer_cast<FunctionCall>(back())->pushArg(it->second, *this);
            } else {
                std::unique_ptr<Variable> var = std::make_unique<Variable>(it->second);
                var->setDebugInfo(it->toDebugInfo());
                //The declaration has to be searched!
                //If no declaration was found, this is a command and should be added as one. 
                bool varFound = var->searchDeclaration(*this);
                if(varFound) {
                    push_back(std::move(var));
                } else {
                    auto cmd = std::make_unique<Command>(it->second);
                    cmd->setDebugInfo(it->toDebugInfo());
                    push_back(std::move(cmd));
                    command = true;
                }
            }
            break;
        }
        case TokenType::NUMBER:
            if(functionCall) {
                boost::static_pointer_cast<FunctionCall>(back())->pushArg(std::make_unique<Number>(it->second));
            }
            break;
        case TokenType::FUNCTION_CALL:
        {
            auto funcCall = std::make_unique<FunctionCall>(it->second);
            funcCall->setDebugInfo(it->toDebugInfo());
            bool found = funcCall->searchDeclaration(rootList);
            if(found) {
                push_back(std::move(funcCall));
                functionCall = true;
            } else {
                // This is not a function call, this is a command.
                auto cmd = std::make_unique<Command>(it->second);
                cmd->setDebugInfo(it->toDebugInfo());
                push_back(std::move(cmd));
                command = true;
            }
            break;
        }
        case TokenType::STRING_LITERAL:
        {
            if(command) {
                auto cmd = std::make_unique<Command>(it->second);
                cmd->setDebugInfo(it->toDebugInfo());
                push_back(std::move(cmd));
            }
            break;
        }
        case TokenType::STRING_LITERAL_MARK:
        {
            if(command) {
                auto cmd = std::make_unique<Command>(it->second);
                cmd->setDebugInfo(it->toDebugInfo());
                push_back(std::move(cmd));
            }
            break;
        }
        case TokenType::STRING_LITERAL_MARK_END:
        {
            if(command) {
                auto cmd = std::make_unique<Command>(it->second);
                cmd->setDebugInfo(it->toDebugInfo());
                push_back(std::move(cmd));
            }
            break;
        }
        case TokenType::PARAM_ITEM_SEPERATOR:
        {
            if(command) {
                auto cmd = std::make_unique<Command>(it->second);
                cmd->setDebugInfo(it->toDebugInfo());
                push_back(std::move(cmd));
            }
            break;
        }
        case TokenType::COMMAND:
        {
            auto cmd = std::make_unique<Command>(it->second);
            cmd->setDebugInfo(it->toDebugInfo());
            push_back(std::move(cmd));
            command = true;
            break;
        }
    }
    return false;
}
}
}
