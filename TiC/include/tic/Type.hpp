#pragma once

#include <string>

namespace tic
{
class Type
{
public:
    Type();
    virtual ~Type();
    
    static bool isType(const std::string &str);
};
}