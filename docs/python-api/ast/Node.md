# ast.Node

Node is the base class of all other nodes. It provides the standard interface to handle nodes and contains the [node type](NodeType).

## .nodeName (str)

Returns the name of the node, based on its type. The names are saved in each node, but can differ if a node saves its own name in a different way to express a certain state. 

## .nodeType ([ast.NodeType](NodeType))

Returns the type of the node. Types are standardized and represent each node with its own ID. A list of all types can be seen in the [ast.NodeType](NodeType) page.

## .debugInfo ([ast.NodeDebugInfo](NodeDebugInfo))

Returns the debug information for a node. This information contains the line and the source file this node originated from, which can be used to print errors in a more meaningful way. How to use this property together with the [error handler](/python-api/tic/ErrorHandler) can be seen an the [Handling Errors](/python-api/Handling-Errors) page.

## .file (str)

Returns the file path this node originated from.

## .line (int)

Returns the line number this node originated from. 

## .full_line (str)

Returns a string of the line this node originated from.
