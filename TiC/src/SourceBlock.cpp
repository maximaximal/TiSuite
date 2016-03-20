#include <tic/SourceBlock.hpp>

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
const std::string &SourceBlock::path()
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
const std::string &SourceBlock::source()
{
    return m_source;
}


}