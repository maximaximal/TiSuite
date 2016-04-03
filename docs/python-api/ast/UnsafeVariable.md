# ast.UnsafeVariable

UnsafeVariable is a derived class of [ast.Node](Node).

UnsafeVariables wrap a variable inside an [unsafe block](Unsafe). They are used to know, which variables are beeing used inside of an unsafe block. 

## .var (str)

Returns the variable name (TiBasic name).

## .type ([tic.Type](/python-api/tic/Type))

Returns the type of the variable in the TiBasic code. Can be useful for typechecking parameters. 
