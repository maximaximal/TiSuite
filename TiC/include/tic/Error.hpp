#pragma once

#include <string>
#include <tic/ast/Node.hpp>

namespace tic
{
class SourceBlock;

class Error
{
public:
    Error(const std::string &msg, tic::ast::NodeDebugInfo *debugInfo);
    Error(const std::string &msg, const std::string &file, uint32_t line);
    Error(const Error &other);
    virtual ~Error();
    
    const std::string& msg() const;
    const std::string& file() const;
    uint32_t line() const;
    const SourceBlock* block() const;
    
    std::string toString();
private:
    std::string m_msg;
    std::string m_file;
    uint32_t m_line;
    SourceBlock *m_block = nullptr;
};
}