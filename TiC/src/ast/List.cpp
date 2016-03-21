#include <tic/ast/List.hpp>

namespace tic 
{
namespace ast 
{
List::List(const char *toStringName) 
    : Node(toStringName)
{

}
List::~List()
{

}
const List::NodeList &List::nodes() const
{
    return m_nodes;
}
List::NodeList &List::nodes()
{
    return m_nodes;
}
void List::push(std::unique_ptr< Node > node)
{
    m_nodes.push_back(std::move(node));
}    
void List::loadFromTokens(SourceBlock::TokenVector &tokens, SourceBlock::TokenVector::iterator &current)
{
    // A normal list has no defined format!
    return;
}
Node *List::back()
{
    return m_nodes.back().get();
}
const Node *List::back() const
{
    return m_nodes.back().get();
}
}
}