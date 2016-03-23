#pragma once

#include <tic/SourceBlock.hpp>
#include <tic/ErrorHandler.hpp>

#include <tic/ast/List.hpp>

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
    
    void initPython(int argc, char** argv);
    void exitPython();
    void generateTICode(const std::string &toolkitPath);
private:
    SourceBlock *m_rootBlock = nullptr;
    ErrorHandler *m_errorHandler;
    
    ast::List *m_rootList = nullptr;
};
}