#pragma once

#include <tic/ast/List.hpp>

namespace tic
{
namespace ast
{
class Scope : public List
{
public:
    Scope(const char *nodeName = "Scope", NodeType nodeType = NodeType::Scope);
    virtual ~Scope();
    
    /**
     * Loads a function from tokens. This has to be called while positioned at the FUNCTION_NAME token. 
     */
    virtual void loadFromTokens(SourceBlock::TokenVector &tokens, SourceBlock::TokenVector::iterator &current, List &rootList);
private:
    
};
}
}