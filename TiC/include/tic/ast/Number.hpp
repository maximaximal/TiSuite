#pragma once

#include <tic/ast/Node.hpp>

namespace tic
{
namespace ast
{
class Number : public Node
{
public:
    Number(double num = 0);
    Number(const std::string &number);
    virtual ~Number();
    
    double val();
    void setVal(double val);
private:
    double m_val;
};
}
}