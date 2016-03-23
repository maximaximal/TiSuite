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
    
    Type::TypeEnum type() const;
    void setType(Type::TypeEnum type);
    
    std::string toString();
    static std::string toStringStatic(const tic::Type *type);
    
    Type();
    Type(const std::string &typeString);
    virtual ~Type();
    
    static bool isType(const std::string &str);
private:
    Type::TypeEnum m_type;
};
}