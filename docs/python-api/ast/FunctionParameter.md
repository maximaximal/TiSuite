# ast.FunctionParameter

FunctionParameter is a derived class of [ast.Node](Node).

A function parameter is given to a [function](Function) to pass arguments over to another function or to define possible parameters of functions in their declaration.

## .type ([tic.Type](/python-api/tic/Type))

The [type](/python-api/tic/Type) of the parameter.

## .name (str)

Returns the name of the variable of this parameter. This is the given variable name in [ast.FunctionCall](FunctionCall) nodes and the to-be variable name in [function](Function) declarations.

## .assigned_name (str)

The target variable of the given argument. This is used in [ast.Unsafe](Unsafe) declarations to pass the given variable to the internal variable inside of the unsafe block.
