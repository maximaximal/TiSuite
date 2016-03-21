#include <tic/Error.hpp>

namespace tic
{
Error::Error(const std::string &msg, const std::string &file, uint32_t line)
    : m_msg(msg), m_file(file), m_line(line)
{
    
}
Error::Error(const Error &other)
    : m_msg(other.msg()), m_file(other.file()), m_line(other.line())
{
    
}
Error::~Error()
{

}
const std::string &Error::msg() const
{
    return m_msg;
}
const std::string &Error::file() const
{
    return m_file;
}
uint32_t Error::line() const
{
    return m_line;
}
}