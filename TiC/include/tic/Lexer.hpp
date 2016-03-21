#pragma once

#include <memory>
#include <map>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/bind.hpp>

#include <tic/Token.hpp>
#include <tic/TokenType.hpp>
#include <tic/SourceBlock.hpp>

namespace tic
{
class Lexer
{
public:
    typedef boost::tokenizer<boost::char_separator<char>>::iterator TokenizerIterator;
    Lexer();
    virtual ~Lexer();
    
    void lex(std::unique_ptr<SourceBlock> block);
    void readTokens(SourceBlock *block);
    
    TokenType::Type typeOfToken(TokenizerIterator begin, TokenizerIterator token, TokenizerIterator end, SourceBlock::TokenVector &tokens);
    bool isScopeCloseInUnsafe(SourceBlock::TokenVector &tokens, std::size_t i);
    inline static bool isValidVarName(const std::string &str) 
    {
        if(str.length() > 0) {
            if(std::isdigit(str[0])) {
                return false;
            }
            return std::find_if(str.begin(), str.end(),
                [](char c) {
                    if(c == '_')
                        return false;
                    else 
                        return !std::isalnum(c);
                }) == str.end();
        }
        return false;
    }
    inline static bool isValidNumber(const std::string &str)
    {
        return std::find_if(str.begin(), str.end(),
            [](char c) {
                if(c == '.')
                    return false;
                else 
                    return !std::isdigit(c);
            }) == str.end();
    }
    
    void setRootBlock(const std::string &rootBlock);
    const std::string& rootBlock() const;
    SourceBlock* rootSourceBlock();
private:
    std::map<std::string, std::unique_ptr<SourceBlock> > m_sourceBlocks;
    std::string m_rootBlock;
};
}