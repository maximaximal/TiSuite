#pragma once

#include <string>

namespace tic
{
class ErrorHandler;

namespace ast
{
class Node
{
public:
    Node(const std::string &toStringName = "Node");
    virtual ~Node();
    
    const std::string& toString();
    
    static ErrorHandler *errorHandler;
protected:
    std::string m_toStringName;
};
}
}