#include <tic/ast/Variable.hpp>
#include <tic/ErrorHandler.hpp>

namespace tic
{
namespace ast
{
Variable::Variable(const std::string &varName)
    : Node("Variable", NodeType::Variable), m_varName(varName)
{
    
}
Variable::~Variable()
{

}
const std::string &Variable::varName() const
{
    return m_varName;
}
VariableDeclaration *Variable::declaration()
{
    return m_declaration;
}
void Variable::setDeclaration(VariableDeclaration *declaration)
{
    m_declaration = declaration;
}
bool Variable::searchDeclaration(List &nodes)
{
    bool found = false;
    for(auto it = nodes.rbegin(); it != nodes.rend() && !found; ++it)
    {
        boost::shared_ptr<VariableDeclaration> declaration = boost::dynamic_pointer_cast<VariableDeclaration>(*it);
        if(declaration) {
            if(declaration->varName() == varName()) {
                setDeclaration(declaration.get());
                found = true;
            }
        }
    }
    return found;
}
}
}