from function import Function
from ast import NodeType

class Unsafe(Function):
    def __init__(self, uns):
        self.name = uns.name
        self.func = uns
        self.variables = []
        self.scan_vars()
        
    def scan_vars(self):
        for node in self.func:
            if node.nodeType == NodeType.UnsafeVariable:
                self.variables.append(node)
