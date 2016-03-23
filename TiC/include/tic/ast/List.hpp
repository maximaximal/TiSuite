#pragma once

#include <memory>
#include <vector>
#include <tic/ast/Node.hpp>
#include <tic/SourceBlock.hpp>
#include <boost/container/vector.hpp>
#include <boost/shared_ptr.hpp>

namespace tic
{
namespace ast
{
class List : public Node, public boost::container::vector<boost::shared_ptr<Node>>
{
public:
    List(const char *toStringName = "List", NodeType type = NodeType::List);
    List(const tic::ast::List &other);
    List(List::iterator begin, List::iterator end);
    virtual ~List();
    
    virtual void loadFromTokens(SourceBlock::TokenVector &tokens, SourceBlock::TokenVector::iterator &current);
};
}
}