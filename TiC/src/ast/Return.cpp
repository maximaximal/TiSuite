#include <tic/ast/Return.hpp>

namespace tic 
{
namespace ast 
{
Return::Return(const std::string &var)
    : Node("Return", NodeType::Return)
{
    
}
Return::Return(std::unique_ptr<Command> cmd)
    : m_command(std::move(cmd)), Node("Return", NodeType::Return)
{
    
}
Return::~Return()
{
    
}

Return::ReturnType Return::returnType()
{
    if(m_command)
        return ReturnType::ReturnCommand;
    return ReturnType::ReturnVariable;
}
Command* Return::returnCmd()
{
    return m_command.get();
}
Variable* Return::returnVar()
{
    return m_variable;
}
}
}
