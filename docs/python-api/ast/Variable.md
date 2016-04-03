# ast.Variable

Variable is a derived class from [ast.Node](Node).

A variable is a wrapper around native calculator variables. It is used to create scopes and to make function arguments and collaboration with other people easier. The value is saved and passed around in different locations, depending on the current scope, to make execution as quick as possible and enable easy programming with a multitude of interconnected functions and programs. 

## .name (str)

Returns the name of the variable. 

## .declaration ([ast.VariableDeclaration](VariableDeclaration))

Returns the delcaration node of this variable, which defines its type and scope. This is guaranteed to be valid, because variables only become variables, if their definition is found somewhere before. 
