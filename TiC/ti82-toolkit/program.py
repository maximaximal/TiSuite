from function import Function
import tic
import ast

class Program(Function):
    def __init__(self, prog, error_handler):
        self.func = prog
        self.name = prog.name
        self.scan_vars()
        
        if len(prog.name) > 8:
            error_handler.handle(tic.Error("A program name cannot be longer than 8 characters!", prog.debugInfo))
