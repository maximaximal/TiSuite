#pragma once

namespace tic
{
class TokenType
{
public:
    enum Type {
        NO_TYPE,
        IGNORE,
        TOKEN_TREE,
        SCOPE_BEGIN,
        SCOPE_END,
        UNSAFE_SCOPE_BEGIN,
        UNSAFE_SCOPE_END,
        VAR_SCOPE_BEGIN,
        VAR_SCOPE_END,
        PARAM_LIST_BEGIN,
        PARAM_LIST_END,
        PARAM_ITEM_SEPERATOR,
        PARAM_ITEM_ASSIGN,
        PARAM_ITEM_TARGET,
        FUNCTION_CALL,
        FUNCTION_KEYWORD,
        UNSAFE_KEYWORD,
        UNSAFE_CONTENT,
        PROGRAM_KEYWORD,
        INCLUDE_KEYWORD,
        INCLUDE_PATH,
        PROGRAM_NAME,
        FUNCTION_RETURN_SEPERATOR,
        RETURN_KEYWORD,
        LINE_COMMENT,
        LINE_COMMENT_END,
        END_STATEMENT,
        STRING_LITERAL_MARK,
        STRING_LITERAL,
        NUMBER,
        TYPE,
        VAR_NAME,
        FUNCTION_NAME,
        COMMAND,
    };
    static bool isKeyword(Type type) {
        switch(type) 
        {
            case FUNCTION_KEYWORD:
                return true;
            case UNSAFE_KEYWORD:
                return true;
            default:
                return false;
        }
    }
    static const char* getTypename(Type type) {
        switch(type)
        {
            case NO_TYPE:
                return "NO_TYPE";
            case IGNORE:
                return "IGNORE";
            case TOKEN_TREE:
                return "TOKEN_TREE";
            case SCOPE_BEGIN:
                return "SCOPE_BEGIN";
            case SCOPE_END:
                return "SCOPE_END";
            case UNSAFE_SCOPE_BEGIN:
                return "UNSAFE_SCOPE_BEGIN";
            case UNSAFE_SCOPE_END:
                return "UNSAFE_SCOPE_END";
            case VAR_SCOPE_BEGIN:
                return "VAR_SCOPE_BEGIN";
            case VAR_SCOPE_END:
                return "VAR_SCOPE_END";
            case PARAM_LIST_BEGIN:
                return "PARAM_LIST_BEGIN";
            case PARAM_LIST_END:
                return "PARAM_LIST_END";
            case PARAM_ITEM_SEPERATOR:
                return "PARAM_ITEM_SEPERATOR";
            case PARAM_ITEM_ASSIGN:
                return "PARAM_ITEM_ASSIGN";
            case PARAM_ITEM_TARGET:
                return "PARAM_ITEM_TARGET";
            case FUNCTION_KEYWORD:
                return "FUNCTION_KEYWORD";
            case FUNCTION_CALL:
                return "FUNCTION_CALL";
            case UNSAFE_KEYWORD:
                return "UNSAFE_KEYWORD";
            case INCLUDE_KEYWORD:
                return "INCLUDE_KEYWORD";
            case INCLUDE_PATH:
                return "INCLUDE_PATH";
            case UNSAFE_CONTENT:
                return "UNSAFE_CONTENT";
            case PROGRAM_KEYWORD:
                return "PROGRAM_KEYWORD";
            case PROGRAM_NAME:
                return "PROGRAM_NAME";
            case FUNCTION_RETURN_SEPERATOR:
                return "FUNCTION_RETURN_SEPERATOR";
            case RETURN_KEYWORD:
                return "RETURN_KEYWORD";
            case LINE_COMMENT:
                return "LINE_COMMENT";
            case LINE_COMMENT_END:
                return "LINE_COMMENT_END";
            case END_STATEMENT:
                return "END_STATEMENT";
            case STRING_LITERAL_MARK:
                return "STRING_LITERAL_MARK";
            case STRING_LITERAL:
                return "STRING_LITERAL";
            case NUMBER:
                return "NUMBER";
            case TYPE:
                return "TYPE";
            case VAR_NAME:
                return "VAR_NAME";
            case FUNCTION_NAME:
                return "FUNCTION_NAME";
            case COMMAND:
                return "COMMAND";
            default:
                return "Name not mapped.";
        }
    }
    
    TokenType() {};
    virtual ~TokenType() {};
    
    virtual inline const char* tokenName() = 0;
    virtual inline TokenType::Type tokenType() = 0;
};
}