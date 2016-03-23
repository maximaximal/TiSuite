#include <tic/ast/Node.hpp>
#include <tic/SourceBlock.hpp>

namespace tic
{
namespace ast 
{
ErrorHandler* Node::errorHandler = nullptr;

const std::string &NodeDebugInfo::getPath() const
{
    return block->path();
}
std::string NodeDebugInfo::getLine() const
{
    return block->printLine(line);
}

Node::Node(const std::string &toStringName, NodeType type)
    : m_toStringName(toStringName), m_type(type)
{

}
Node::~Node()
{

}
const std::string &Node::toString() const
{
    return m_toStringName;
}
NodeType Node::type() const
{
    return m_type;
}
NodeDebugInfo *Node::debugInfo() 
{
    return &m_debugInfo;
}
void Node::setDebugInfo(const NodeDebugInfo &nodeDebugInfo)
{
    m_debugInfo = nodeDebugInfo;
}
const std::string &Node::file() const
{
    return m_debugInfo.getPath();
}
uint32_t Node::line() const
{
    return m_debugInfo.line;
}
std::string Node::printLine() const
{
    return m_debugInfo.getLine();
}
bool Node::operator==(Node *node) const
{
    if(m_toStringName == node->toString()
        && m_type == node->type())
        return true;
    return false;
}
}
}
