#pragma once

#include <memory>
#include <list>
#include <tic/ast/Node.hpp>
#include <tic/SourceBlock.hpp>

namespace tic
{
namespace ast
{
class List : public Node
{
public:
    typedef std::list<std::shared_ptr<Node>> NodeList;
    List(const char *toStringName = "List");
    virtual ~List();
    
    void push(std::unique_ptr<Node> node);
    
    Node * back();
    const Node* back() const;
    
    virtual void loadFromTokens(SourceBlock::TokenVector &tokens, SourceBlock::TokenVector::iterator &current);
    
    NodeList& nodes();
    const NodeList& nodes() const;
private:
    NodeList m_nodes;
};
}
}