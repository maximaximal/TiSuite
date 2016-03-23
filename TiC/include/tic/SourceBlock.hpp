#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <tuple>

#include <tic/TokenType.hpp>
#include <tic/ast/Node.hpp>

namespace tic
{
class SourceBlock
{
public:
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
        ast::NodeDebugInfo toDebugInfo()
        {
            ast::NodeDebugInfo info;
            info.line = line;
            info.block = source;
            return info;
        }
    };
    typedef TokenStruct TokenPair;
    typedef std::vector<TokenPair> TokenVector;
    SourceBlock();
    virtual ~SourceBlock();
    
    void setString(const std::string &source);
    const std::string& source() const;
    
    void setPath(const std::string &path);
    void readFromFile(const std::string &path);
    const std::string& path() const;
    
    void prependSourceBlock(SourceBlock *block);
    
    TokenVector& tokenVector();
    const TokenVector& tokenVector() const;
    
    std::string printLine(uint32_t line) const;
private:
    std::string m_source;
    std::string m_filePath;
    
    TokenVector m_tokenVector;
};
}