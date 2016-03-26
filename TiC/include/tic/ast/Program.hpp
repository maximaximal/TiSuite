#pragma once

#include <tic/ast/Function.hpp>

namespace tic 
{
namespace ast 
{
class Program : public Function
{
public:
    Program(const std::string &programName, const char *nodeName = "Program", NodeType nodeType = NodeType::Program);
    virtual ~Program();
    
    const std::string& tiBasic();
    void setTIBasic(const std::string &tibasic);
private:
    std::string m_tibasic;
};
}
}