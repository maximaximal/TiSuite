#include <tic/ast/Node.hpp>

namespace tic
{
namespace ast 
{
ErrorHandler* Node::errorHandler = nullptr;

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
bool Node::operator==(Node *node) const
{
    if(m_toStringName == node->toString()
        && m_type == node->type())
        return true;
    return false;
}
}
}
