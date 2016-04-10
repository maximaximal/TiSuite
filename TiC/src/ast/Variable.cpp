#include <tic/ast/Variable.hpp>
#include <tic/ErrorHandler.hpp>
#include <tic/ast/Function.hpp>
#include <tic/ast/FunctionParameter.hpp>

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
    if(nodes.type() == NodeType::Function || nodes.type() == NodeType::Program) {
        Function *func = static_cast<Function*>(&nodes);
        for(auto param : *(func->parameters()))
        {
            boost::shared_ptr<FunctionParameter> declaration = boost::dynamic_pointer_cast<FunctionParameter>(param);
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
