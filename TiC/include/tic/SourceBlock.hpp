#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <tuple>

#include <tic/TokenType.hpp>

namespace tic
{
class SourceBlock
{
public:
    struct TokenPos {
        std::string file;
        uint32_t line;
    };
    struct TokenStruct {
        TokenType::Type first;
        std::string second;
        SourceBlock *source = nullptr;
        uint32_t line = 0;
        
        std::string getFile() 
        {
            if(source) {
                return source->path();
            } 
            return "";
        }
    };
    typedef TokenStruct TokenPair;
    typedef std::vector<TokenPair> TokenVector;
    SourceBlock();
    virtual ~SourceBlock();
    
    void setString(const std::string &source);
    const std::string& source();
    
    void setPath(const std::string &path);
    void readFromFile(const std::string &path);
    const std::string& path();
    
    TokenVector& tokenVector();
    const TokenVector& tokenVector() const;
private:
    std::string m_source;
    std::string m_filePath;
    
    TokenVector m_tokenVector;
};
}