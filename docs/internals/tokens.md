Tokens
======

These tokens are used in the internal compiler programming and can be useful during debugging problems with the compiler. 

NO_TYPE
-------

The token has no type.

IGNORE
------

The IGNORE token has no effect. It is simply ignored. 

SCOPE_BEGIN
----------

A scope opener is a `{`.

SCOPE_END
-----------

A scope closer is a `}`. It has to close another scope introduced by SCOPE_BEGIN. 

UNSAFE_SCOPE_BEGIN
------------------

Begins an unsafe scope. It is also started with `{` but treated differently. 

UNSAFE_SCOPE_END
----------------

End an unsafe scope. It is ended with `}`. The individual `}` in the unsafe block are counted to match each other out, until the unsafe block is closed. Example: 

```
unsafe (a : A)
{
    A -> A
    {A, A} * 3      // Match each other out!
}
```

VAR_SCOPE_BEGIN
---------------

A variable scope beginner is a `(`. It has to be in front of a VAR_NAME token. Variables and statements inside a variable scope get evaluated before the ones outside of it. 

VAR_SCOPE_END
-------------

A variable scope ender is a `)`. It has to be after a VAR_NAME token. It ends the local variable scope. It has to be after another VAR_SCOPE_BEGIN token. 

PARAM_LIST_BEGIN
----------------

A parameter list beginner is a `(`. It has to be after a FUNCTION_KEYWORD or a UNSAFE_KEYWORD token.

PARAM_LIST_END
--------------

A param list ender is a `)`. It has to be after a PARAM_LIST_BEGIN token. 

PARAM_ITEM_SEPERATOR
--------------------

A parameter item seperator (`,`) seperates the individual items in a parameter list. Example: `function sth(num varA, num varB) {}`.

PARAM_ITEM_ASSIGN
-----------------

A parameter item assignment operator is a `:` that assigns the parameter name to a given variable on the calculator (hardware variable).

PARAM_ITEM_TARGET
-----------------

The target of an assignment operator in an argument list. This is the target variable in unsafe blocks. 

FUNCTION_CALL
-------------

A function call is a valid variable name with a PARAM_LIST_BEGIN and PARAM_LIST_END token after it. 

FUNCTION_KEYWORD
----------------

A function keyword is the word `function`, followed by a PARAM_LIST_BEGIN and a PARAM_LIST_END operator pair with any amount of parameters and an optional return type. It has to be followed by a SCOPE_BEGIN token. 

UNSAFE_KEYWORD
--------------

A unsafe keyword marks the beginning of an unsafe block. It has to be followed by a string literal or a scope (load file or use local unsafe content).

PROGRAM_KEYWORD
---------------

A program keyword marks the definition of a program. A program is listed in the calculator, so this is the real entry point to the language. 

UNSAFE_CONTENT
--------------

Unsafe content is the inner unsafe content of inline unsafe blocks. This contains many different tokens, including whitespace. 

FUNCTION_RETURN_SEPERATOR
-------------------------

A function return seperator is the `:` after a function declaration, which defines the function return type. 

FUNCTION_RETURN_TYPE
--------------------

A function return type is the function return type, which may be any type of the type system (like `num`, `str`, ...).

RETURN_KEYWORD
--------------

The function return keyword ends a function and optionally returns a given variable. The variabe must match the return type defined in FUNCTION_RETURN_TYPE. 

LINE_COMMENT
------------

A line comment starts with a `//` and goes until the end of the line is reached. 

LINE_COMMENT_END
----------------

The end of a line comment. It is reached at a newline `\n`.

END_STATEMENT
-------------

A statement ender is a `;`. It ends statements (usually lines).

STRING_LITERAL_MARK
-------------------

A string literal mark is a `"`. It marks the beginning or the end of a string literal like `"Hello World"`. 

STRING_LITERAL
--------------

A string literal is the content between two STRING_LITERAL_MARK tokens. Strings are defined this way. 

NUMBER
------

A number is either an integer (natural number) or a decimal number with a `.` marking the decimal point. It can also be written as `.something`, which then means `0.something`.

TYPE
----

The type of a variable or a return type. Stands in front of a valid VAR_NAME token. 

VAR_NAME
--------

The instance name of a variable. Stands after a valid TYPE token. Example: `num numberVariable;`.

FUNCTION_NAME
-------------

The name of the function. has to be after a FUNCTION_KEYWORD token.

PROGRAM_NAME
------------

The name of a program. This stands after a PROGRAM_KEYWORD token and has a PARAM_LIST_BEGIN and PARAM_LIST_END token after it.
