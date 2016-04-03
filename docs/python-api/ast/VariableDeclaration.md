# ast.VariableDeclaration

VariableDeclaration is a derived class of [ast.Node](Node).

A variable declaration defines the type and scope of a [variable](Variable). It is required for a variable to exist. If no declaration is found, the valid variable becomes invalid and is converted into an [ast.Command](Command) node instead.

## .name (str)

The name of the declared variable.

## .type ([tic.Type](/python-api/tic/Type))

Returns the [type](/python-api/tic/Type) of the declared variable. 
