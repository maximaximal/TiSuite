Abstract Syntax Tree
====================

The abstract syntax tree (ast) is the representation of the complete sourcecode of the program 
in the compiler. After it was generated out of the token stream, it is converted into the final 
tibasic code by the python compiler script. 

The AST is built from a root node (an [ast.List](/python-api/ast/List) object), which contains several 
[functions](/python-api/ast/Function), [programs](/python-api/ast/Program), and [unsafe blocks](/python-api/ast/Unsafe). To 
better understand the AST, the python reference is a good start. 
