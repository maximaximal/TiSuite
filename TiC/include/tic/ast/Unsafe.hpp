#pragma once

#include <tic/ast/Function.hpp>

namespace tic 
{
namespace ast 
{
/**
 * @brief The unsafe Block is a node derived from a function. 
 * 
 * The internal list doesn't contain internal nodes, but 
 * instead contains the used variables in order of their usage (no variable is stored twice).
 * The variables are stroed in tic::ast::UnsafeVariable instances. 
 */
class Unsafe : public Function 
{
public:
    Unsafe(const std::string &name);
    virtual ~Unsafe();
    
    void appendContent(const std::string &content);
    void loadContentFromFile(const std::string &path);
    
    // Parses the given tokens and tries to find variables contained in the unsafe block. 
    virtual void loadFromTokens(SourceBlock::TokenVector &tokens, SourceBlock::TokenVector::iterator &current, List &rootList);
    
    const std::string& content();
    void setContent(const std::string &content);
    Type::TypeEnum isUnsafeVariable(const std::string &str);
    bool variableAlreadyDefined(const std::string &str);
    
    /**
     * @brief Checks the given variable for occurences in the possible tokens. 
     * 
     * Returns 0 if the variable is no token. 
     * Returns 1 if the variable is a known TiBasic token. 
     * Returns 2 if the variable is a known TiBasic variable. 
     */
    static int checkStringVariableType(const std::string &str);
    static std::string generateTiTokensList();
    static std::string generateTiVarsList();
private:
    std::string m_content;
};
}
}
