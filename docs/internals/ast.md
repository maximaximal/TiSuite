Abstract Syntax Tree
====================

The abstract syntax tree (ast) is the representation of the complete sourcecode of the program 
in the compiler. After it was generated out of the token stream, it is converted into the final 
tibasic code by the python compiler script. 

A list of all node types follows. 

Node
----

A normal node is the most basic node of all. It is the base class for everx other node in the system. 

Function
--------

A function node encapsulates a function, including all its contents. It is a derived class from the List node 
and contains all nodes inside the function scope. 

FunctionCall
------------

A function call is the call to a function. It represents a function to be called. It contains the function name 
and the parameters. 
