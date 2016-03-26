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

#include <boost/container/vector.hpp>
#include <tic/ast/List.hpp>
#include <tic/ast/Function.hpp>
#include <tic/ast/FunctionCall.hpp>
#include <tic/ast/FunctionParameter.hpp>
#include <tic/ast/Variable.hpp>
#include <tic/ast/Number.hpp>
#include <tic/ast/Command.hpp>
#include <tic/ast/Program.hpp>
#include <tic/ast/VariableDeclaration.hpp>

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
using namespace boost::python;
BOOST_PYTHON_MODULE(tic)
{
    enum_<tic::Type::TypeEnum>("ValueType")
        .value("Number", tic::Type::NUMBER)
        .value("Matrix", tic::Type::MATRIX)
        .value("List", tic::Type::LIST)
        .value("String", tic::Type::STRING)
    ;
    class_<tic::Error>("Error", init<std::string, ast::NodeDebugInfo*>())
        .add_property("msg", make_function(&tic::Error::toString))
    ;
    class_<tic::ErrorHandler, boost::noncopyable>("ErrorHandler", boost::python::no_init)
        .def("handle", &tic::ErrorHandler::handleError)
    ;
    class_<tic::Type>("Type")
        .add_property("type", &tic::Type::type, &tic::Type::setType)
        .add_property("typeName", make_function(&tic::Type::toString))
    ;
}
BOOST_PYTHON_MODULE(ast)
{
    enum_<ast::NodeType>("NodeType")
        .value("Node", ast::NodeType::Node)
        .value("List", ast::NodeType::List)
        .value("Scope", ast::NodeType::Scope)
        .value("Function", ast::NodeType::Function)
        .value("FunctionParameter", ast::NodeType::FunctionParameter)
        .value("FunctionCall", ast::NodeType::FunctionCall)
        .value("Variable", ast::NodeType::Variable)
        .value("VariableDeclaration", ast::NodeType::VariableDeclaration)
        .value("Number", ast::NodeType::Number)
        .value("Command", ast::NodeType::Command)
    ;
    class_<ast::NodeDebugInfo, boost::noncopyable>("NodeDebugInfo")
        .add_property("file", make_function(&ast::NodeDebugInfo::getPath, return_value_policy<copy_const_reference>()))
        .add_property("line", &ast::NodeDebugInfo::line)
    ;
    class_<ast::Node, boost::noncopyable>("Node", boost::python::no_init)
        .add_property("nodeName", make_function(&ast::Node::toString, return_value_policy<copy_const_reference>()))
        .add_property("nodeType", make_function(&ast::Node::type))
        .add_property("debugInfo", make_function(&ast::Node::debugInfo, return_value_policy<reference_existing_object>()))
        .add_property("file", make_function(&ast::Node::file, return_value_policy<copy_const_reference>()))
        .add_property("line", make_function(&ast::Node::line))
        .add_property("full_line", make_function(&ast::Node::printLine))
    ;
    class_<ast::List, boost::shared_ptr<ast::List>, bases<ast::Node>, boost::noncopyable>("List", boost::python::no_init)
        .def(vector_indexing_suite<ast::List, true>())
        .def("nodes", &ast::List::getNodesOfType, return_value_policy<manage_new_object>())
    ;
    class_<ast::Scope, bases<ast::List>, boost::noncopyable>("Scope", boost::python::no_init)
    ;
    class_<ast::Number, bases<ast::Node>, boost::noncopyable>("Number", boost::python::no_init)
        .add_property("val", &ast::Number::val, &ast::Number::setVal)
    ;
    
    register_ptr_to_python<boost::shared_ptr<ast::Node>>();
    
    class_<ast::Function, bases<ast::Scope>>("Function", boost::python::no_init)
        .add_property("parameters", make_function(&ast::Function::parameters, return_value_policy<reference_existing_object>()))
        .add_property("returnType", make_function(&ast::Function::returnType, return_value_policy<reference_existing_object>()))
        .add_property("name", make_function(&ast::Function::functionName, return_value_policy<copy_const_reference>()))
    ;
    class_<ast::Program, bases<ast::Function>>("Program", boost::python::no_init)
        .add_property("tibasic", make_function(&ast::Program::tiBasic, return_value_policy<copy_const_reference>()),
            make_function(&ast::Program::setTIBasic))
    ;
    class_<ast::FunctionParameter, bases<ast::Node>, boost::noncopyable>("FunctionParameter", boost::python::no_init)
        .add_property("type", make_function(&ast::FunctionParameter::type, return_value_policy<reference_existing_object>()), 
            make_function(&ast::FunctionParameter::setType))
        .add_property("name", make_function(&ast::FunctionParameter::varName, return_value_policy<copy_const_reference>()), 
            make_function(&ast::FunctionParameter::setVarName))
    ;
    class_<ast::FunctionCall, bases<ast::Node>, boost::noncopyable>("FunctionCall", boost::python::no_init)
        .add_property("name", make_function(&ast::FunctionCall::functionName, return_value_policy<copy_const_reference>()))
        .add_property("declaration", make_function(&ast::FunctionCall::declaration, return_value_policy<reference_existing_object>()))
        .add_property("args", make_function(&ast::FunctionCall::args, return_value_policy<reference_existing_object>()))
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
    class_<ast::Command, bases<ast::Node>, boost::noncopyable>("Command", boost::python::no_init)
        .add_property("cmd", make_function(&ast::Command::command, return_value_policy<copy_const_reference>()),
            make_function(&ast::Command::setCommand))
    ;
}

void initPythonModules()
{
    PyImport_AppendInittab("ast", PyInit_ast);
    PyImport_AppendInittab("tic", PyInit_tic);
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
        
        PyObject* sysPath = PySys_GetObject("path");
        PyList_Insert( sysPath, 0, PyUnicode_FromString(toolkitPath.c_str()));
        
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