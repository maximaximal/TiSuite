from ast import NodeType

class Function:
    def __init__(self, func):
        self.name = func.name
        self.func = func
        self.variables = []
        self.scan_vars()
    
    def scan_vars(self):
        for node in self.func:
            if node.nodeType == NodeType.VariableDeclaration:
                self.variables.append(node)
        
    def add_cmd(self, cmd):
        self.commands.append(cmd)
        
    def add_var(self, var):
        self.vars.append(var)
