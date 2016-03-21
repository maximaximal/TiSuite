#include <tic/ErrorHandler.hpp>
#include <iostream>

using std::cout;
using std::endl;

namespace tic
{
ErrorHandler::ErrorHandler()
{

}
ErrorHandler::~ErrorHandler()
{

}
bool ErrorHandler::handleError(const Error &error)
{
    cout << "ERROR: FILE \"" << error.file() << "\" line " << error.line() << ": " << error.msg() << endl;
    push(error);
}
void ErrorHandler::push(const Error &error)
{
    m_errorSink.push_back(error);
}
}