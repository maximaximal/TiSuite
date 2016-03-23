#pragma once

#include <string>

namespace tic
{
class ErrorHandler;

namespace ast
{
enum class NodeType
{
    Node,
    List,
    Function,
    FunctionDecaration,
    FunctionCall,
    FunctionParameter,
    Variable,
    VariableDeclaration,
};
class Node
{
public:
    Node(const std::string &toStringName = "Node", NodeType type = NodeType::Node);
    virtual ~Node();
    
    const std::string& toString() const;
    NodeType type() const;
    bool operator==(Node *node) const;
    
    static ErrorHandler *errorHandler;
protected:
    std::string m_toStringName;
    NodeType m_type;
};
}
}