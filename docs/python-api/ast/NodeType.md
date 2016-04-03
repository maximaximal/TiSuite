# ast.NodeType

A node type represents a specific type of node, usually a subclass of the [node](Node) base class. 

# Possible Types

The possible node types can be seen in the following table. 

NodeType | Matching Class
-------- | --------------
.Node    | [ast.Node](Node)
.List    | [ast.List](List)
.Scope   | [ast.Scope](Scope)
.Proram  | [ast.Program](Program)
.Unsafe  | [ast.Unsafe](Unsafe)
.UnsafeVariable  | [ast.UnsafeVariable](UnsafeVariable)
.Function| [ast.Function](Function)
.FunctionParameter | [ast.FunctionParameter](FunctionParameter)
.FunctionCall | [ast.FunctionCall](FunctionCall)
.Variable| [ast.Variable](Variable)
.VariableDeclaration | [ast.VariableDeclaration](VariableDeclaration)
.Number| [ast.Number](Number)
.Command | [ast.Command](Command)

