#pragma once

#include <tic/SourceBlock.hpp>

namespace tic
{
class TokenParser
{
public:
    TokenParser();
    virtual ~TokenParser();
    
    void parseBlock();
};
}