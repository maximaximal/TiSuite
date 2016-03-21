#pragma once

#include <string>

namespace tic
{
class Error
{
public:
    Error(const std::string &msg, const std::string &file, uint32_t line);
    Error(const Error &other);
    virtual ~Error();
    
    const std::string& msg() const;
    const std::string& file() const;
    uint32_t line() const;
private:
    std::string m_msg;
    std::string m_file;
    uint32_t m_line;
};
}