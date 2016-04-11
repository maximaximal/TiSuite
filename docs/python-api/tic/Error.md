# tic.Error

A Error contains an error message of any kind. The message can be set at will, while the location information (where this error occured in the source) depends on a node. 

## .__init__(msg, debugInfo)

Initializes an Error object. Example: `Error("Test", node.debugInfo)`

## .msg (str)

Returns the contained error message as a string.
