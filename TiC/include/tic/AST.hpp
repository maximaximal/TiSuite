#pragma once

#include <tic/SourceBlock.hpp>
#include <tic/ErrorHandler.hpp>

namespace tic
{
/*
 * @brief The AST-Class is the manager class for an abstract syntax tree.
 */
class AST
{
public:
    AST(ErrorHandler *errorHandler);
    virtual ~AST();
    
    void generateFromTokenizedBlock(SourceBlock *block);
private:
    SourceBlock *m_rootBlock = nullptr;
    ErrorHandler *m_errorHandler;
};
}