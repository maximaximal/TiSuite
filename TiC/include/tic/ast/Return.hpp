#pragma once

#include <tic/ast/Node.hpp>
#include <tic/ast/Command.hpp>
#include <tic/ast/Variable.hpp>

namespace tic
{
namespace ast
{
class Return : public Node
{
public:
    enum ReturnType {
        ReturnVariable,
        ReturnCommand,
    };
    
    Return(const std::string &returnVar);
    Return(std::unique_ptr<Command> cmd);
    virtual ~Return();
    
    ReturnType returnType();
    
    Command* returnCmd();
    Variable* returnVar();
private:
    std::unique_ptr<Command> m_command;
    Variable *m_variable = nullptr;
};
}
}
