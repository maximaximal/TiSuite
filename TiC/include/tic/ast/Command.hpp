#pragma once

#include <tic/ast/Node.hpp>

namespace tic
{
namespace ast 
{
/**
 * @brief A command encapsulates a calculator command. 
 */
class Command : public Node
{
public:
    Command(const std::string &cmd);
    virtual ~Command();
    
    const std::string& command();
    void setCommand(const std::string &cmd);
    void appendCommand(const std::string &cmd);
private:
    std::string m_command;
};
}
}