import tic
import ast
from ast import NodeType

from memory import Memory
from function import Function
from unsafe import Unsafe
from program import Program

# This is the toolkit for a TI82-Stats Calculator
# It is not fuly optimized, advice is welcome!

print("Initializing calculator memory")
ti_memory = Memory()

funcs = []
unsafes = []
programs = []

def handle_func(func):
    funcs.append(Function(func))

def handle_unsafe(uns):
    unsafes.append(Unsafe(uns))

def handle_program(prog):
    programs.append(Program(prog, error_handler))

# Begin Parsing
print("Parsing AST")
for unsafe_block in root_list.nodes(NodeType.Unsafe):
    handle_unsafe(unsafe_block)

for func in root_list.nodes(NodeType.Function):
    handle_func(func)
    out_str = ""
    for node in func:
        print("  - Node: " + node.nodeName)
        if node.nodeType == NodeType.Command:
            print("   : CMD: " + node.cmd)
            out_str += node.cmd
        if node.nodeType == NodeType.Variable:
            print("   : VAR: " + node.name + " with type " + node.declaration.type.typeName)
            out_str += node.declaration.type.typeName
    out.set_file(func.name, out_str)

for prog in root_list.nodes(NodeType.Program):
    handle_program(prog)
    
print("Assigning internal variables")
for uns in unsafes:
    print("Unsafe " + uns.name)
    for var in uns.variables:
        print("Var: " + var.var)
        
for func in funcs:
    print("Function " + func.name)
    for var in func.variables:
        print("Var: " + var.name)

for prog in programs:
    print("Program " + prog.name)
    out.set_file(prog.name + ".txt", "Test")
