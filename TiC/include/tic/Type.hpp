#pragma once

#include <string>

namespace tic
{
class Type
{
public:
    enum TypeEnum {
        STRING,
        NUMBER,
        MATRIX,
        LIST
    };
    
    Type();
    Type(const std::string &typeString);
    virtual ~Type();
    
    static bool isType(const std::string &str);
private:
    Type::TypeEnum m_type;
};
}