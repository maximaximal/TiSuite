#include <tic/TokenTree.hpp>

namespace tic 
{
TokenTree::TokenTree()
{

}
TokenTree::~TokenTree()
{

}
TokenTree::TokenVector &TokenTree::tokens()
{
    return m_tokens;
}
}