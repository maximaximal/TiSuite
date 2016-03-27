#include <tic/AST.hpp>

#define BOOST_PYTHON_STATIC_LIB

#include <tic/ast/Node.hpp>
#include <tic/ast/Unsafe.hpp>
#include <tic/ast/Function.hpp>
#include <tic/ast/Program.hpp>
#include <iostream>

using std::cout;
using std::endl;

namespace tic
{
AST::AST(ErrorHandler *errorHandler, OutputMgr *outputMgr)
    : m_errorHandler(errorHandler), m_outputMgr(outputMgr)
{
    ast::Node::errorHandler = errorHandler;
}
AST::~AST()
{
    if(m_rootList)
        delete m_rootList;
}
void AST::generateFromTokenizedBlock(SourceBlock *block)
{
    m_rootBlock = nullptr;
    m_rootList = new ast::List("RootList", ast::NodeType::List);
    
    SourceBlock::TokenVector &tokens = block->tokenVector();
    
    //Parse flags
    bool functionDefinition = false;
    bool programDefinition = false;
    bool unsafeDefinition = false;
    
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
            case tic::TokenType::INCLUDE_PATH:
                
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
            case tic::TokenType::PROGRAM_KEYWORD:
                programDefinition = true;
                break;
            case tic::TokenType::UNSAFE_KEYWORD:
                unsafeDefinition = true;
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
                    function->setDebugInfo(it->toDebugInfo());
                    function->loadFromTokens(tokens, it, *m_rootList);
                    functionDefinition = false;
                    
                    m_rootList->push_back(std::move(function));
                }
                break;
            case tic::TokenType::PROGRAM_NAME:
                if(programDefinition) {
                    std::unique_ptr<ast::Program> program = std::make_unique<ast::Program>(it->second);
                    program->setDebugInfo(it->toDebugInfo());
                    program->loadFromTokens(tokens, it, *m_rootList);
                    programDefinition = false;
                    
                    m_rootList->push_back(std::move(program));
                }
            case tic::TokenType::UNSAFE_NAME:
            {
                if(unsafeDefinition) {
                    std::unique_ptr<ast::Unsafe> uns = std::make_unique<ast::Unsafe>(it->second);
                    uns->setDebugInfo(it->toDebugInfo());
                    uns->loadFromTokens(tokens, it, *m_rootList);
                    unsafeDefinition = false;
                    
                    m_rootList->push_back(std::move(uns));
                }
                break;
            }
            case tic::TokenType::COMMAND:
                break;
        }
    }
}
}
