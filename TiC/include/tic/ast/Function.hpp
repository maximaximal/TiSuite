#pragma once

#include <tic/Type.hpp>
#include <tic/ast/Scope.hpp>

namespace tic
{
namespace ast
{
class Function : public Scope
{
public:
    Function(const std::string &functionName, const char *nodeName = "Function", NodeType nodeType = NodeType::Function);
    virtual ~Function();
    
    const std::string& functionName() const;
    
    /**
     * Loads a function from tokens. This has to be called while positioned at the FUNCTION_NAME token. 
     */
    virtual void loadFromTokens(SourceBlock::TokenVector &tokens, SourceBlock::TokenVector::iterator &current, List &rootList);
    
    List* parameters();
    
    Type* returnType();
protected:
    Type m_returnType;
    List m_parameters;
private:
    std::string m_functionName;
};
}
}