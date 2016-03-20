#pragma once

#include <string>
#include <fstream>
#include <vector>

#include <tic/TokenType.hpp>

namespace tic
{
class SourceBlock
{
public:
    typedef std::pair<TokenType::Type, std::string> TokenPair;
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