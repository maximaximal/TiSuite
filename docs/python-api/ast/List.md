# ast.List

List is a derived class of [ast.Node](Node).

Lists can contain nodes of any type and are iteratable. They can also be empty.

## .nodes([ast.NodeType](NodeType)) ([ast.List](List))

Searches the contained nodes and returns a new list of all nodes with the given type. 
