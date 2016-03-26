#include <tic/ast/Number.hpp>
#include <boost/lexical_cast.hpp>

namespace tic 
{
namespace ast 
{
Number::Number(double num)
    : Node("Number", NodeType::Number), m_val(num)
{

}
Number::Number(const std::string &strNum)
    : Node("Number", NodeType::Number), m_val(boost::lexical_cast<double>(strNum))
{

}
ast::Number::~Number()
{
    
}
void ast::Number::setVal(double val)
{
    m_val = val;
}
double ast::Number::val()
{
    return m_val;
}
}
}