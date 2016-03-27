#pragma once

#include <string>

namespace tic
{
class ErrorHandler;
class SourceBlock;

namespace ast
{
enum class NodeType
{
    Node,
    List,
    Scope,
    Function,
    Program,
    Unsafe,
    UnsafeVariable,
    FunctionDecaration,
    FunctionCall,
    FunctionParameter,
    Variable,
    VariableDeclaration,
    Number,
    Command,
};
struct NodeDebugInfo
{
    SourceBlock* block;
    uint32_t line;
    
    const std::string& getPath() const;
    std::string getLine() const;
};
class Node
{
public:
    Node(const std::string &toStringName = "Node", NodeType type = NodeType::Node);
    virtual ~Node();
    
    const std::string& toString() const;
    NodeType type() const;
    bool operator==(Node *node) const;
    
    NodeDebugInfo* debugInfo();
    void setDebugInfo(const NodeDebugInfo &nodeDebugInfo);
    uint32_t line() const;
    const std::string& file() const;
    std::string printLine() const;
    
    static ErrorHandler *errorHandler;
protected:
    std::string m_toStringName;
    NodeType m_type;
    NodeDebugInfo m_debugInfo;
};
}
}