#pragma once

#include <vector>
#include <tic/Error.hpp>

namespace tic
{
class ErrorHandler
{
public:
    ErrorHandler();
    virtual ~ErrorHandler();
    
    virtual bool handleError(const Error &error);
protected:
    void push(const Error &error);
private:
    std::vector<Error> m_errorSink;
};
}