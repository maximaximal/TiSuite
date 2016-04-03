# ast.Function

Function is a derived class of [ast.Scope](Scope).

Represents a function with its parameters, return type, its name and contents. A function can be colled from other locations using an [ast.FunctionCall](FunctionCall) node.

## .parameters ([ast.List](List)) 

Returns a [list](List) containing all [function parameters](FunctionParameter) of this function.

## .returnType ([tic.Type](/python-api/tic/Type))

Returns a [type](/python-api/tic/Type), which represents the return type of the function.

## .name (str)

Returns the name of this function as a string.
