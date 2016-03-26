#include <tic/ast/Program.hpp>

namespace tic 
{
namespace ast 
{
Program::Program(const std::string &programName, const char *nodeName, NodeType nodeType)
    : Function(programName, nodeName, nodeType)
{

}
Program::~Program()
{

}
const std::string &Program::tiBasic()
{
    return m_tibasic;
}
void Program::setTIBasic(const std::string &tibasic)
{
    m_tibasic = tibasic;
}
}
}