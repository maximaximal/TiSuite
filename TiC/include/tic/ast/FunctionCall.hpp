#pragma once

#include <tic/ast/List.hpp>

namespace tic
{
namespace ast
{
/**
 * Describes a function call. The node list contains variable nodes to pass to the function.
 */
class FunctionCall : public List
{
public:
    FunctionCall(const std::string &functionName);
    virtual ~FunctionCall();
    
    const std::string& functionName() const;
private:
    std::string m_functionName;
};
}
}