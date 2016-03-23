#include <tic/ast/List.hpp>

namespace tic 
{
namespace ast 
{
List::List(const char *toStringName, NodeType type) 
    : Node(toStringName, type) 
{

}
List::List(const tic::ast::List &other)
    : Node(other.toString(), other.type()), boost::container::vector<boost::shared_ptr<Node>>()
{
    
}
List::List(List::iterator begin, List::iterator end)
    : Node("List", NodeType::List), boost::container::vector<boost::shared_ptr<Node>>(begin, end)
{

}

List::~List()
{

}
void List::loadFromTokens(SourceBlock::TokenVector &tokens, SourceBlock::TokenVector::iterator &current)
{
    // A normal list has no defined format!
    return;
}

}
}