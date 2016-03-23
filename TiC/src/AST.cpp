#include <tic/AST.hpp>

#define BOOST_PYTHON_STATIC_LIB

#include <tic/ast/Node.hpp>
#include <tic/ast/Function.hpp>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/exec.hpp>
#include <boost/python/converter/shared_ptr_to_python.hpp>
#include <Python.h>
#include <iostream>

#include <tic/ast/Function.hpp>
#include <tic/ast/FunctionCall.hpp>
#include <tic/ast/FunctionParameter.hpp>
#include <tic/ast/Variable.hpp>
#include <tic/ast/VariableDeclaration.hpp>

using namespace boost::python;
using std::cout;
using std::endl;

// Thanks to http://stackoverflow.com/a/8032108
wchar_t *GetWC(const char *c)
{
    const size_t cSize = strlen(c)+1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs (wc, c, cSize);

    return wc;
}

namespace tic
{
BOOST_PYTHON_MODULE(tic)
{
    enum_<tic::Type::TypeEnum>("ValueType")
        .value("Number", tic::Type::NUMBER)
        .value("Matrix", tic::Type::MATRIX)
        .value("List", tic::Type::LIST)
        .value("String", tic::Type::STRING)
    ;
    class_<tic::Error>("Error", init<std::string, std::string, int>())
        .def("__str__", &tic::Error::toString)
    ;
    class_<tic::ErrorHandler, boost::noncopyable>("ErrorHandler", boost::python::no_init)
        .def("handle", &tic::ErrorHandler::handleError)
    ;
    class_<tic::Type>("Type")
        .add_property("type", &tic::Type::type, &tic::Type::setType)
        .def("__str__", &tic::Type::toString)
    ;
}
BOOST_PYTHON_MODULE(ast)
{
    enum_<ast::NodeType>("NodeType")
        .value("Node", ast::NodeType::Node)
        .value("List", ast::NodeType::List)
        .value("Function", ast::NodeType::Function)
        .value("FunctionParameter", ast::NodeType::FunctionParameter)
        .value("FunctionCall", ast::NodeType::FunctionCall)
        .value("Variable", ast::NodeType::Variable)
        .value("VariableDeclaration", ast::NodeType::VariableDeclaration)
    ;
    class_<ast::Node, boost::noncopyable>("Node", boost::python::no_init)
        .def("__str__", &ast::Node::toString, return_value_policy<copy_const_reference>())
        .add_property("nodeType", make_function(&ast::Node::type))
    ;
    class_<ast::List, bases<ast::Node>, boost::noncopyable>("List", boost::python::no_init)
        .def(vector_indexing_suite<ast::List>())
    ;
    class_<ast::Function, bases<ast::List>>("Function", boost::python::no_init)
        .add_property("parameters", make_function(&ast::Function::parameters, return_value_policy<reference_existing_object>()))
        .add_property("returnType", make_function(&ast::Function::returnType, return_value_policy<reference_existing_object>()))
        .def("name", &ast::Function::functionName, return_value_policy<copy_const_reference>())
    ;
    class_<ast::FunctionParameter, bases<ast::Node>, boost::noncopyable>("FunctionParameter", boost::python::no_init)
        .add_property("type", make_function(&ast::FunctionParameter::type, return_value_policy<reference_existing_object>()), 
            make_function(&ast::FunctionParameter::setType))
        .add_property("name", make_function(&ast::FunctionParameter::varName, return_value_policy<copy_const_reference>()), 
            make_function(&ast::FunctionParameter::setVarName))
    ;
    class_<ast::FunctionCall, bases<ast::Node>, boost::noncopyable>("FunctionCall", boost::python::no_init)
        .add_property("name", make_function(&ast::FunctionCall::functionName, return_value_policy<copy_const_reference>()))
    ;
    class_<ast::VariableDeclaration, bases<ast::Node>, boost::noncopyable>("VariableDeclaration", boost::python::no_init)
        .add_property("name", make_function(&ast::VariableDeclaration::varName, return_value_policy<copy_const_reference>()), 
            make_function(&ast::VariableDeclaration::setVarName))
        .add_property("type", make_function(&ast::VariableDeclaration::type, return_value_policy<reference_existing_object>()), 
            make_function(&ast::VariableDeclaration::setType))
    ;
    class_<ast::Variable, bases<ast::Node>, boost::noncopyable>("Variable", boost::python::no_init)
        .add_property("name", make_function(&ast::Variable::varName, return_value_policy<copy_const_reference>()))
        .add_property("declaration", make_function(&ast::Variable::declaration, return_value_policy<reference_existing_object>()), 
            make_function(&ast::Variable::setDeclaration))
    ;
    register_ptr_to_python<std::shared_ptr<ast::Node>>();
}

void initPythonModules()
{
    PyImport_AppendInittab("ast", PyInit_ast);
    PyImport_AppendInittab("tic", PyInit_tic);
}

AST::AST(ErrorHandler *errorHandler)
    : m_errorHandler(errorHandler)
{
    ast::Node::errorHandler = errorHandler;
}
AST::~AST()
{
    if(m_rootList)
        delete m_rootList;
}
void AST::generateFromTokenizedBlock(SourceBlock *block)
{
    m_rootBlock = nullptr;
    m_rootList = new ast::List("RootList", ast::NodeType::List);
    
    SourceBlock::TokenVector &tokens = block->tokenVector();
    
    //Parse flags
    bool functionDefinition = false;
    
    for(auto it = tokens.begin(); it != tokens.end(); ++it)
    {
        switch(it->first)
        {
            case tic::TokenType::NO_TYPE:
                //This is an error. There has to be a type!
                m_errorHandler->handleError(Error("NO_TYPE token is invalid!", it->getFile(), it->line));
                break;
            case tic::TokenType::IGNORE:
                //Is ignored
                break;
            case tic::TokenType::TOKEN_TREE:
                // Nothing for now.
                break;
            case tic::TokenType::SCOPE_BEGIN:
                break;
            case tic::TokenType::SCOPE_END:
                break;
            case tic::TokenType::UNSAFE_SCOPE_BEGIN:
                break;
            case tic::TokenType::UNSAFE_SCOPE_END:
                break;
            case tic::TokenType::VAR_SCOPE_BEGIN:
                break;
            case tic::TokenType::VAR_SCOPE_END:
                break;
            case tic::TokenType::PARAM_LIST_BEGIN:
                break;
            case tic::TokenType::PARAM_LIST_END:
                break;
            case tic::TokenType::PARAM_ITEM_SEPERATOR:
                break;
            case tic::TokenType::PARAM_ITEM_ASSIGN:
                break;
            case tic::TokenType::PARAM_ITEM_TARGET:
                break;
            case tic::TokenType::FUNCTION_KEYWORD:
                functionDefinition = true;
                break;
            case tic::TokenType::UNSAFE_KEYWORD:
                break;
            case tic::TokenType::UNSAFE_CONTENT:
                break;
            case tic::TokenType::FUNCTION_RETURN_SEPERATOR:
                break;
            case tic::TokenType::RETURN_KEYWORD:
                break;
            case tic::TokenType::LINE_COMMENT:
                break;
            case tic::TokenType::LINE_COMMENT_END:
                break;
            case tic::TokenType::END_STATEMENT:
                break;
            case tic::TokenType::STRING_LITERAL_MARK:
                break;
            case tic::TokenType::STRING_LITERAL:
                break;
            case tic::TokenType::NUMBER:
                break;
            case tic::TokenType::TYPE:
                break;
            case tic::TokenType::VAR_NAME:
                break;
            case tic::TokenType::FUNCTION_NAME:
                if(functionDefinition) {
                    std::unique_ptr<ast::Function> function = std::make_unique<ast::Function>(it->second);
                    function->loadFromTokens(tokens, it);
                    functionDefinition = false;
                    
                    m_rootList->push_back(std::move(function));
                }
                break;
            case tic::TokenType::ASSIGN_OPERATOR:
                break;
            case tic::TokenType::CALC_OPERATOR:
                break;
        }
    }
}
void AST::initPython(int argc, char **argv)
{
    initPythonModules();
    
    wchar_t *name = GetWC(argv[0]);
    Py_SetProgramName(name);
    delete name;
    Py_InitializeEx(0);
    
}
void AST::exitPython()
{
    
}
void AST::generateTICode(const std::string &toolkitPath)
{
    using namespace boost::python;
    
    try {
        object main = import("__main__");
        object globals(main.attr("__dict__"));
        
        object tic_module((handle<>(PyImport_ImportModule("tic"))));
        globals["tic"] = tic_module;
        
        object ast_module((handle<>(PyImport_ImportModule("ast"))));
        globals["ast"] = ast_module;
        
        globals["error_handler"] = boost::ref(m_errorHandler);
        globals["root_list"] = boost::ref(m_rootList);
        
        std::string file = toolkitPath;
        file += "/toolkit.py";
        
        cout << "Executing python toolkit file \"" << file << "\"." << endl;
        
        object result = exec_file(file.c_str(), globals, globals);
    } catch(error_already_set) {
        PyErr_Print();
        PyErr_Clear();
    }
}
}
