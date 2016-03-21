#include <tic/ast/Variable.hpp>
#include <tic/ErrorHandler.hpp>

namespace tic
{
namespace ast
{
Variable::Variable(const std::string &varName)
    : Node("Variable"), m_varName(varName)
{
    
}
Variable::~Variable()
{

}
const std::string &Variable::varName()
{
    return m_varName;
}
const VariableDeclaration *Variable::declaration() const
{
    return m_declaration;
}
VariableDeclaration *Variable::declaration()
{
    return m_declaration;
}
void Variable::setDeclaration(VariableDeclaration *declaration)
{
    m_declaration = declaration;
}
void Variable::searchDeclaration(List::NodeList &nodes)
{
    bool found = false;
    for(auto it = nodes.rbegin(); it != nodes.rend() && !found; ++it)
    {
        std::shared_ptr<VariableDeclaration> declaration = std::dynamic_pointer_cast<VariableDeclaration>(*it);
        if(declaration) {
            setDeclaration(declaration.get());
            found = true;
        }
    }
    if(!found) {
        errorHandler->handleError(Error("Variable \"" + varName() + "\" is never declared!", "", 0));
    }
}
}
}