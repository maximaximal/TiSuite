#pragma once

#include <tic/Type.hpp>
#include <tic/ast/List.hpp>

namespace tic
{
namespace ast
{
class Function : public List
{
public:
    Function(const std::string &functionName);
    virtual ~Function();
    
    const std::string& functionName() const;
    
    /**
     * Loads a function from tokens. This has to be called while positioned at the FUNCTION_NAME token. 
     */
    virtual void loadFromTokens(SourceBlock::TokenVector &tokens, SourceBlock::TokenVector::iterator &current);
    
    List& parameters();
    const List& parameters() const;
    
    Type& returnType();
    const Type& returnType() const;
private:
    Type m_returnType;
    List m_parameters;
    std::string m_functionName;
};
}
}