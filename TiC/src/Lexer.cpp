#include <tic/Lexer.hpp>
#include <tic/SourceBlock.hpp>
#include <tic/TokenTree.hpp>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <tic/Type.hpp>

using std::cout;
using std::endl;

namespace tic
{
Lexer::Lexer()
{

}
Lexer::~Lexer()
{

}
void Lexer::lex(std::unique_ptr< SourceBlock > block)
{
    const std::string &path = block->path();
    if(m_sourceBlocks.count(path) == 0) {
        readTokens(block.get());
        
        m_sourceBlocks[path] = std::move(block);
    } else {
        // We already have this sourceblock, it doesn't need to be loaded. 
    }
}
void Lexer::readTokens(SourceBlock *block)
{
    SourceBlock::TokenVector &tokens = block->tokenVector();
    
    SourceBlock::TokenPair tokenPair;
    tokenPair.first = TokenType::IGNORE;
    tokenPair.second = "";
    
    // Insert a filler pair to avoid bugs in the detection code. 
    tokens.push_back(tokenPair);
    
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    
    boost::char_separator<char> sep("\t", "+-*/,=:;)([]{}\n\" ");
    
    tokenizer tok(block->source(), sep);
    
    for(auto token = tok.begin(); token != tok.end(); ++token)
    {
        tokenPair.first = typeOfToken(tok.begin(), token, tok.end(), tokens);
        tokenPair.second = *token;
        
        if(tokenPair.first != TokenType::IGNORE) {
            tokens.push_back(tokenPair);
        }
    }
    tokens.erase(tokens.begin());
    
    //Debug display
    std::string display;
    for(auto token : tokens) 
    {
        display = token.second;
        if(token.second == "\n") {
            display = "\\n";
        } else if(token.second == "\"") {
            display = "\"";
        }
        cout << "Token \"" << display << "\"" << ": " << TokenType::getTypename(token.first) << endl;
    }
    
}
TokenType::Type Lexer::typeOfToken(TokenizerIterator begin, TokenizerIterator token, TokenizerIterator end, SourceBlock::TokenVector &tokens)
{
    TokenType::Type type = TokenType::NO_TYPE;
    bool found = false;
    if(*token == "{") {
        found = false;
        for(auto revIt = tokens.rbegin(); revIt != tokens.rend() && found == false; ++revIt) 
        {
            switch(revIt->first)
            {
                case TokenType::UNSAFE_CONTENT:
                    type = TokenType::UNSAFE_CONTENT;
                    found = true;
                    break;
                case TokenType::LINE_COMMENT:
                    type = TokenType::LINE_COMMENT;
                    found = true;
                    break;
                case TokenType::UNSAFE_SCOPE_BEGIN:
                    type = TokenType::UNSAFE_CONTENT;
                    found = true;
                    break;
                case TokenType::UNSAFE_KEYWORD:
                    type = TokenType::UNSAFE_SCOPE_BEGIN;
                    found = true;
                    break;
                case TokenType::PROGRAM_KEYWORD:
                    type = TokenType::SCOPE_BEGIN;
                    found = true;
                    break;
                case TokenType::END_STATEMENT:
                    type = TokenType::SCOPE_BEGIN;
                    found = true;
                    break;
                case TokenType::STRING_LITERAL:
                    type = TokenType::STRING_LITERAL;
                    found = true;
                    break;
                case TokenType::STRING_LITERAL_MARK:
                    type = TokenType::STRING_LITERAL;
                    found = true;
                    break;
                case TokenType::FUNCTION_KEYWORD:
                    type = TokenType::SCOPE_BEGIN;
                    found = true;
                    break;
                default: 
                    type = TokenType::SCOPE_BEGIN;
                    break;
            }
        }
    } else if(*token == "}") {
        found = false;
        for(auto revIt = tokens.rbegin(); revIt != tokens.rend() && found == false; ++revIt) 
        {
            switch(revIt->first)
            {
                case TokenType::UNSAFE_SCOPE_BEGIN:
                    if(isScopeCloseInUnsafe(tokens, tokens.size() - 1 - (revIt - tokens.rbegin()))) {
                        type = TokenType::UNSAFE_CONTENT;
                    } else {
                        type = TokenType::UNSAFE_SCOPE_END;
                    }
                    found = true;
                    break;
                case TokenType::LINE_COMMENT:
                    type = TokenType::LINE_COMMENT;
                    found = true;
                    break;
                case TokenType::END_STATEMENT:
                    type = TokenType::SCOPE_END;
                    found = true;
                    break;
                case TokenType::FUNCTION_KEYWORD:
                    type = TokenType::SCOPE_END;
                    found = true;
                    break;
                case TokenType::STRING_LITERAL:
                    type = TokenType::STRING_LITERAL;
                    found = true;
                    break;
                case TokenType::STRING_LITERAL_MARK:
                    type = TokenType::STRING_LITERAL;
                    found = true;
                    break;
                case TokenType::UNSAFE_SCOPE_END:
                    type = TokenType::SCOPE_END;
                    found = true;
                    break;
                default: 
                    type = TokenType::SCOPE_END;
                    break;
            }
        }
    } else if(*token == "(") {
        if(tokens.back().first == TokenType::UNSAFE_CONTENT) {
            type = TokenType::UNSAFE_CONTENT;
        } 
        // A '(' can be a PARAM_LIST_BEGIN token or a VAR_SCOPE_BEGIN token. 
        // It depends on the keyword before the current position. It has to be another keyword to be a PARAM_LIST_BEGIN token. 
        else {
            found = false;
            for(auto revIt = tokens.rbegin(); revIt != tokens.rend() && found == false; ++revIt) 
            {
                switch(revIt->first)
                {
                    case TokenType::FUNCTION_KEYWORD:
                        type = TokenType::PARAM_LIST_BEGIN;
                        found = true;
                        break;
                    case TokenType::UNSAFE_KEYWORD:
                        type = TokenType::PARAM_LIST_BEGIN;
                        found = true;
                        break;
                    case TokenType::VAR_NAME:
                        type = TokenType::PARAM_LIST_BEGIN;
                        revIt->first = TokenType::FUNCTION_CALL;
                        found = true;
                        break;
                    case TokenType::END_STATEMENT:
                        type = TokenType::VAR_SCOPE_BEGIN;
                        found = true;
                        break;
                    case TokenType::STRING_LITERAL:
                        type = TokenType::STRING_LITERAL;
                        found = true;
                        break;
                    case TokenType::STRING_LITERAL_MARK:
                        type = TokenType::STRING_LITERAL;
                        found = true;
                        break;
                    default: 
                        type = TokenType::VAR_SCOPE_BEGIN;
                        break;
                }
            }
        }
    } else if(*token == ")") {
        // A ')' can be a PARAM_LIST_END token or a VAR_SCOPE_END token. 
        // If there is an unclosed PARAM_LIST_BEGIN token before the current ')', it will be a PARAM_LIST_END token. 
        
        found = false;
        for(auto revIt = tokens.rbegin(); revIt != tokens.rend() && found == false; ++revIt) 
        {
            switch(revIt->first) 
            {
                case TokenType::UNSAFE_CONTENT: 
                    // If there was already unsafe content before, this doesn't end it!
                    type = TokenType::UNSAFE_CONTENT;
                    found = true;
                    break;
                case TokenType::PARAM_LIST_END:
                    // There was already a parameter list before. Therefore, this must be a variable scope ')'. 
                    type = TokenType::VAR_SCOPE_END;
                    found = true;
                    break;
                case TokenType::PARAM_LIST_BEGIN:
                    // There was an opened parameter list before. This must be a parameter list close!
                    type = TokenType::PARAM_LIST_END;
                    found = true;
                    break;
                case TokenType::VAR_SCOPE_END: 
                    // There was a closed variable scope before. This must be a variable scope. This improves performance. 
                    type = TokenType::VAR_SCOPE_END;
                    found = true;
                    break;
                case TokenType::VAR_SCOPE_BEGIN:
                    // There was an unclosed variable scope before. Because there are no variable scopes in parameter lists, this
                    // must be a variable scope end. 
                    type = TokenType::VAR_SCOPE_END;
                    found = true;
                    break;
                case TokenType::STRING_LITERAL:
                    type = TokenType::STRING_LITERAL;
                    found = true;
                    break;
                case TokenType::STRING_LITERAL_MARK:
                    type = TokenType::STRING_LITERAL;
                    found = true;
                    break;
                default:
                    // Not enough information!
                    type = TokenType::NO_TYPE;
                    break;
            }
        }
    } else if(*token == ",") {
        switch(tokens.back().first)
        {
            case TokenType::UNSAFE_CONTENT:
                type = TokenType::UNSAFE_CONTENT;
                break;
            default: 
                type = TokenType::PARAM_ITEM_SEPERATOR;
                break;
        }
    } else if(*token == ":") {
        
        found = false;
        for(auto revIt = tokens.rbegin(); revIt != tokens.rend() && found == false; ++revIt) 
        {
            switch(revIt->first)
            {
                case TokenType::PARAM_LIST_END:
                    // Used in function declarations like this function() : num {}
                    type = TokenType::FUNCTION_RETURN_SEPERATOR;
                    found = true;
                    break;
                case TokenType::VAR_NAME: 
                    // Used in unsafe keywords like this: unsafe(varA : A) "test.82a"
                    type = TokenType::PARAM_ITEM_ASSIGN;
                    found = true;
                    break;
                case TokenType::UNSAFE_CONTENT:
                    // There was unsafe content before: this is also unsafe. 
                    type = TokenType::UNSAFE_CONTENT;
                    found = true;
                    break;
                case TokenType::STRING_LITERAL:
                    type = TokenType::STRING_LITERAL;
                    found = true;
                    break;
                case TokenType::STRING_LITERAL_MARK:
                    type = TokenType::STRING_LITERAL;
                    found = true;
                    break;
                default: 
                    // Not enough information!
                    type = TokenType::NO_TYPE;
                    break;
            }
        }
    } else if(*token == "\n") {
        // A newline is not important most of the time. It is only important for comments and unsafe content. 
        switch(tokens.back().first) 
        {
            case TokenType::LINE_COMMENT: 
                type = TokenType::LINE_COMMENT_END;
                break;
            case TokenType::UNSAFE_CONTENT:
                type = TokenType::UNSAFE_CONTENT;
                break;
            default: 
                type = TokenType::IGNORE;
                break;
        }
    } else if(*token == " ") {
        switch(tokens.back().first) 
        {
            case TokenType::STRING_LITERAL:
                type = TokenType::STRING_LITERAL;
                break;
            case TokenType::STRING_LITERAL_MARK:
                type = TokenType::STRING_LITERAL;
                break;
            case TokenType::UNSAFE_CONTENT:
                type = TokenType::UNSAFE_CONTENT;
                break;
            case TokenType::LINE_COMMENT:
                type = TokenType::LINE_COMMENT;
                break;
            default:
                type = TokenType::IGNORE;
                break;
        }
    } else if(*token == ";") {
        switch(tokens.back().first)
        {
            case TokenType::STRING_LITERAL:
                type = TokenType::STRING_LITERAL;
                break;
            case TokenType::STRING_LITERAL_MARK:
                type = TokenType::STRING_LITERAL;
                break;
            case TokenType::UNSAFE_CONTENT:
                type = TokenType::UNSAFE_CONTENT;
                break;
            default:
                type = TokenType::END_STATEMENT;
                break;
        }
    } else if(*token == "function") {
        switch(tokens.back().first)
        {
            case TokenType::STRING_LITERAL:
                type = TokenType::STRING_LITERAL;
                break;
            case TokenType::STRING_LITERAL_MARK:
                type = TokenType::STRING_LITERAL;
                break;
            case TokenType::UNSAFE_CONTENT:
                type = TokenType::UNSAFE_CONTENT;
                break;
            case TokenType::LINE_COMMENT:
                type = TokenType::LINE_COMMENT;
                break;
            default:
                type = TokenType::FUNCTION_KEYWORD;
                break;
        }
    } else if(*token == "unsafe") {
        switch(tokens.back().first)
        {
            case TokenType::STRING_LITERAL:
                type = TokenType::STRING_LITERAL;
                break;
            case TokenType::STRING_LITERAL_MARK:
                type = TokenType::STRING_LITERAL;
                break;
            case TokenType::UNSAFE_CONTENT:
                type = TokenType::UNSAFE_CONTENT;
                break;
            case TokenType::LINE_COMMENT:
                type = TokenType::LINE_COMMENT;
                break;
            default:
                type = TokenType::UNSAFE_KEYWORD;
                break;
        }
    } else if(*token == "program") {
        switch(tokens.back().first)
        {
            case TokenType::UNSAFE_CONTENT:
                type = TokenType::UNSAFE_CONTENT;
                break;
            case TokenType::STRING_LITERAL:
                type = TokenType::STRING_LITERAL;
                break;
            case TokenType::STRING_LITERAL_MARK:
                type = TokenType::STRING_LITERAL;
                break;
            case TokenType::LINE_COMMENT:
                type = TokenType::LINE_COMMENT;
                break;
            default:
                type = TokenType::PROGRAM_KEYWORD;
                break;
        }
    } else if(*token == "include") {
        switch(tokens.back().first)
        {
            case TokenType::UNSAFE_CONTENT:
                type = TokenType::UNSAFE_CONTENT;
                break;
            case TokenType::STRING_LITERAL:
                type = TokenType::STRING_LITERAL;
                break;
            case TokenType::STRING_LITERAL_MARK:
                type = TokenType::STRING_LITERAL;
                break;
            case TokenType::LINE_COMMENT:
                type = TokenType::LINE_COMMENT;
                break;
            default:
                type = TokenType::INCLUDE_KEYWORD;
                break;
        }
    } else if(Type::isType(*token)) {
        switch(tokens.back().first) 
        {
            case TokenType::STRING_LITERAL:
                type = TokenType::STRING_LITERAL;
                break;
            case TokenType::STRING_LITERAL_MARK:
                type = TokenType::STRING_LITERAL;
                break;
            case TokenType::LINE_COMMENT:
                type = TokenType::LINE_COMMENT;
                break;
            case TokenType::UNSAFE_CONTENT:
                type = TokenType::UNSAFE_CONTENT;
                break;
            default: 
                type = TokenType::TYPE;
                break;
        }
    } else if(*token == "\"") {
        found = false;
        for(auto revIt = tokens.rbegin(); revIt != tokens.rend() && found == false; ++revIt) 
        {
            switch(revIt->first)
            {
                case TokenType::UNSAFE_CONTENT:
                    type = TokenType::UNSAFE_CONTENT;
                    found = true;
                    break;
                case TokenType::LINE_COMMENT:
                    type = TokenType::LINE_COMMENT;
                    found = true;
                    break;
                case TokenType::ASSIGN_OPERATOR:
                    type = TokenType::STRING_LITERAL_MARK;
                    found = true;
                    break;
                default:
                    type = TokenType::STRING_LITERAL_MARK;
                    break;
            }
        }
    } else if(*token == "=") {
        found = false;
        for(auto revIt = tokens.rbegin(); revIt != tokens.rend() && found == false; ++revIt) 
        {
            switch(revIt->first)
            {
                case TokenType::UNSAFE_CONTENT:
                    type = TokenType::UNSAFE_CONTENT;
                    found = true;
                    break;
                case TokenType::LINE_COMMENT:
                    type = TokenType::LINE_COMMENT;
                    found = true;
                    break;
                case TokenType::CALC_OPERATOR:
                    // The assign operator has to be extended to match the operator!
                    revIt->first = TokenType::ASSIGN_OPERATOR;
                    revIt->second.append(*token);
                    type = TokenType::IGNORE;
                    found = true;
                    break;
                case TokenType::STRING_LITERAL:
                    type = TokenType::STRING_LITERAL;
                    found = true;
                    break;
                case TokenType::STRING_LITERAL_MARK:
                    type = TokenType::STRING_LITERAL;
                    found = true;
                    break;
                case TokenType::VAR_NAME:
                    type = TokenType::ASSIGN_OPERATOR;
                    found = true;
                    break;
                default:
                    type = TokenType::NO_TYPE;
                    break;
            }
        }
    } else if(*token == "+" || *token == "-" || *token == "*" || *token == "/") {
        found = false;
        for(auto revIt = tokens.rbegin(); revIt != tokens.rend() && found == false; ++revIt) 
        {
            switch(revIt->first) {
                case TokenType::UNSAFE_CONTENT:
                    type = TokenType::UNSAFE_CONTENT;
                    found = true;
                    break;
                case TokenType::LINE_COMMENT:
                    type = TokenType::LINE_COMMENT;
                    found = true;
                    break;
                case TokenType::VAR_NAME:
                    type = TokenType::CALC_OPERATOR;
                    found = true;
                    break;
                case TokenType::NUMBER:
                    type = TokenType::CALC_OPERATOR;
                    found = true;
                    break;
                default:
                    type = TokenType::CALC_OPERATOR;
                    break;
            }
        }
    } else if(isValidVarName(*token)) {
        // Alphanumeric tokens can mean: 
        //   * VAR_NAME 
        //   * FUNCTION_NAME
        //   * STRING_LITERAL
        //   * UNSAFE_LINE
        found = false;
        for(auto revIt = tokens.rbegin(); revIt != tokens.rend() && found == false; ++revIt) 
        {
            switch(revIt->first)
            {
                case TokenType::UNSAFE_CONTENT:
                    type = TokenType::UNSAFE_CONTENT;
                    found = true;
                    break;
                case TokenType::LINE_COMMENT:
                    type = TokenType::LINE_COMMENT;
                    found = true;
                    break;
                case TokenType::STRING_LITERAL:
                    type = TokenType::STRING_LITERAL;
                    found = true;
                    break;
                case TokenType::FUNCTION_KEYWORD:
                    type = TokenType::FUNCTION_NAME;
                    found = true;
                    break;
                case TokenType::TYPE:
                    // Declaration of a variable.
                    type = TokenType::VAR_NAME;
                    found = true;
                    break;
                case TokenType::ASSIGN_OPERATOR:
                    //Assignments
                    type = TokenType::VAR_NAME;
                    found = true;
                    break;
                case TokenType::STRING_LITERAL_MARK:
                    type = TokenType::STRING_LITERAL;
                    found = true;
                    break;
                default:
                    type = TokenType::IGNORE;
                    break;
            }
        }
    } else if(isValidNumber(*token)) {
        found = false;
        for(auto revIt = tokens.rbegin(); revIt != tokens.rend() && found == false; ++revIt) 
        {
            switch(revIt->first)
            {
                case TokenType::UNSAFE_CONTENT:
                    type = TokenType::UNSAFE_CONTENT;
                    found = true;
                    break;
                case TokenType::LINE_COMMENT:
                    type = TokenType::LINE_COMMENT;
                    found = true;
                    break;
                case TokenType::ASSIGN_OPERATOR:
                    type = TokenType::NUMBER;
                    found = true;
                    break;
                case TokenType::END_STATEMENT:
                    type = TokenType::NUMBER;
                    found = true;
                    break;
                case TokenType::CALC_OPERATOR:
                    type = TokenType::NUMBER;
                    found = true;
                    break;
                default:
                    type = TokenType::NO_TYPE;
                    break;
            }
        }
    }
    return type;
}
bool Lexer::isScopeCloseInUnsafe(SourceBlock::TokenVector &tokens, std::size_t i)
{
    int counter = 0;
    for(auto it = (tokens.begin() + i); it != tokens.end(); ++it)
    {
        if(it->first == TokenType::UNSAFE_CONTENT) {
            if(it->second == "{") {
                ++counter;
            } else if(it->second == "}") {
                --counter;
            }
        }
    }
    if(counter == 0) {
        return false;
    }
    return true;
}
void Lexer::setRootBlock(const std::string &rootBlock)
{
    m_rootBlock = rootBlock;
}
const std::string &Lexer::rootBlock() const
{
    return m_rootBlock;
}
SourceBlock *Lexer::rootSourceBlock()
{
    if(m_sourceBlocks.count(m_rootBlock) == 1)
        return m_sourceBlocks[m_rootBlock].get();
    return nullptr;
}

}