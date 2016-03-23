#include <tic/SourceBlock.hpp>
#include <boost/tokenizer.hpp>
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;

namespace tic
{
SourceBlock::SourceBlock()
{

}
SourceBlock::~SourceBlock()
{

}
const SourceBlock::TokenVector &SourceBlock::tokenVector() const
{
    return m_tokenVector;
}
SourceBlock::TokenVector &SourceBlock::tokenVector()
{
    return m_tokenVector;
}
const std::string &SourceBlock::path() const
{
    return m_filePath;
}
void SourceBlock::readFromFile(const std::string &path)
{
    m_filePath = path;
    std::ifstream file(path);
    file.seekg(0, std::ios::end);
    m_source.reserve(file.tellg());
    file.seekg(0, std::ios::beg);
    m_source.assign((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
}
void SourceBlock::setPath(const std::string &path)
{
    m_filePath = path;
}
void SourceBlock::setString(const std::string &source)
{
    m_source = source;
}
void SourceBlock::prependSourceBlock(SourceBlock *block)
{
    //Inserts the tokens to the internal vector. 
    m_tokenVector.insert(m_tokenVector.begin(), block->tokenVector().begin(), block->tokenVector().end());
}
const std::string &SourceBlock::source() const
{
    return m_source;
}
std::string SourceBlock::printLine(uint32_t line) const
{
    std::string source_line = "";
    std::istringstream isstream(m_source);
    uint16_t lineCount = 1;
    while(std::getline(isstream, source_line))
    {
        if(lineCount == line)
            return source_line;
        ++lineCount;
    }
    return "Could not extract line";
}

}