#include <tic/ast/Node.hpp>

namespace tic
{
namespace ast 
{
ErrorHandler* Node::errorHandler = nullptr;

Node::Node(const std::string &toStringName)
    : m_toStringName(toStringName)
{

}
Node::~Node()
{

}
const std::string &Node::toString()
{
    return m_toStringName;
}
}
}
