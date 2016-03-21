#include <tic/AST.hpp>
#include <tic/ast/Node.hpp>
#include <tic/ast/Function.hpp>

namespace tic
{
AST::AST(ErrorHandler *errorHandler)
    : m_errorHandler(errorHandler)
{
    ast::Node::errorHandler = errorHandler;
}
AST::~AST()
{

}
void AST::generateFromTokenizedBlock(SourceBlock *block)
{
    m_rootBlock = nullptr;
    
    SourceBlock::TokenVector &tokens = block->tokenVector();
    
    //Parse flags
    bool functionDefinition = false;
    
    for(auto it = tokens.begin(); it != tokens.end(); ++it)
    {
        switch(it->first)
        {
            case tic::TokenType::NO_TYPE:
                //This is an error. There has to be a type!
                m_errorHandler->handleError(Error("NO_TYPE token is invalid!", it->getFile(), it->line));
                break;
            case tic::TokenType::IGNORE:
                //Is ignored
                break;
            case tic::TokenType::TOKEN_TREE:
                // Nothing for now.
                break;
            case tic::TokenType::SCOPE_BEGIN:
                break;
            case tic::TokenType::SCOPE_END:
                break;
            case tic::TokenType::UNSAFE_SCOPE_BEGIN:
                break;
            case tic::TokenType::UNSAFE_SCOPE_END:
                break;
            case tic::TokenType::VAR_SCOPE_BEGIN:
                break;
            case tic::TokenType::VAR_SCOPE_END:
                break;
            case tic::TokenType::PARAM_LIST_BEGIN:
                break;
            case tic::TokenType::PARAM_LIST_END:
                break;
            case tic::TokenType::PARAM_ITEM_SEPERATOR:
                break;
            case tic::TokenType::PARAM_ITEM_ASSIGN:
                break;
            case tic::TokenType::PARAM_ITEM_TARGET:
                break;
            case tic::TokenType::FUNCTION_KEYWORD:
                functionDefinition = true;
                break;
            case tic::TokenType::UNSAFE_KEYWORD:
                break;
            case tic::TokenType::UNSAFE_CONTENT:
                break;
            case tic::TokenType::FUNCTION_RETURN_SEPERATOR:
                break;
            case tic::TokenType::RETURN_KEYWORD:
                break;
            case tic::TokenType::LINE_COMMENT:
                break;
            case tic::TokenType::LINE_COMMENT_END:
                break;
            case tic::TokenType::END_STATEMENT:
                break;
            case tic::TokenType::STRING_LITERAL_MARK:
                break;
            case tic::TokenType::STRING_LITERAL:
                break;
            case tic::TokenType::NUMBER:
                break;
            case tic::TokenType::TYPE:
                break;
            case tic::TokenType::VAR_NAME:
                break;
            case tic::TokenType::FUNCTION_NAME:
                if(functionDefinition) {
                    std::unique_ptr<ast::Function> function = std::make_unique<ast::Function>(it->second);
                    function->loadFromTokens(tokens, it);
                    functionDefinition = false;
                }
                break;
            case tic::TokenType::ASSIGN_OPERATOR:
                break;
            case tic::TokenType::CALC_OPERATOR:
                break;
        }
    }
}
}
