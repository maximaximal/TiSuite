#pragma once

#include <vector>
#include <tic/TokenType.hpp>
#include <tic/Token.hpp>

namespace tic
{
/**
* @brief Describes a tree of tokens and is a base class for all tokens containing other tokens. 
* 
* The value of the token tree is parsed further down and is replicated inside the tree. 
*/
class TokenTree : public TokenType
{
public:
    typedef std::vector<Token> TokenVector;
    
    TokenTree();
    virtual ~TokenTree();
    
    virtual inline const char* tokenName() 
    {
        return "Token Tree";
    }
    virtual inline TokenType::Type tokenType()
    {
        return TokenType::TOKEN_TREE;
    }
    
    TokenVector& tokens();
private:
    TokenVector m_tokens;
};
}