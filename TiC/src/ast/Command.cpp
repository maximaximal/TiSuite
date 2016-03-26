#include <tic/ast/Command.hpp>

namespace tic 
{
namespace ast 
{
Command::Command(const std::string &cmd)
    : Node("Command",NodeType::Command), m_command(cmd)
{

}
Command::~Command()
{

}
void Command::setCommand(const std::string &cmd)
{
    m_command = cmd;
}
void Command::appendCommand(const std::string &cmd)
{
    m_command.append(cmd);
}
const std::string &Command::command()
{
    return m_command;
}
}
}