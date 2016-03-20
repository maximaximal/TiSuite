#pragma once

#include <string>
#include <tic/TokenType.hpp>

namespace tic
{
struct Token
{
    /**
     * Only holds the type of the token.
     */
    TokenType::Type type;
    /**
     * Holds the token object for every token. 
     */
    TokenType *token = nullptr;
};
}