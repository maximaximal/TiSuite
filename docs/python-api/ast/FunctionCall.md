# ast.FunctionCall

FunctionCall is a derived class of [ast.Node](Node).

A function call is the representation of a call to a function. It wraps the function nam eto be called, a reference to its declaration and the given parameters. The function to be called by a function call is guaranteed to exist.

A function call can be used to call [unsafe blocks](Unsafe), [programs](Program) or [functions](Function). The type has to checked, once the declaration of the function to be called has been fetched. 

## .name (str)

Returns the name of the function to be called.

## .declaration ([ast.Function](Function))

Returns the [ast.Function](Function) this function call refers to.

## .args ([ast.List](List))

Returns a list containing [ast.FunctionParameter](FunctionParameter) nodes, which are given as parameters to this function call.
