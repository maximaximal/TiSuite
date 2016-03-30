from register import Register
from list import List

class Memory:
    def __init__(self):
        pass
    
    lists = {"L1": List("L1"),
             "L2": List("L2"),
             "L3": List("L3"),
             "L4": List("L4"),
             "L5": List("L5"),
             "L6": List("L6"),
             }
    
    registers = {"A": Register("A"),
                 "B": Register("B"),
                 "C": Register("C"),
                 "D": Register("D"),
                 "E": Register("E"),
                 "F": Register("F"),
                 "G": Register("G"),
                 "H": Register("H"),
                 "I": Register("I"),
                 "J": Register("J"),
                 "K": Register("K"),
                 "L": Register("L"),
                 "M": Register("M"),
                 "N": Register("N"),
                 "O": Register("O"),
                 "P": Register("P"),
                 "Q": Register("Q"),
                 "R": Register("R"),
                 "S": Register("S"),
                 "T": Register("T"),
                 "U": Register("U"),
                 "V": Register("V"),
                 "W": Register("W"),
                 "X": Register("X"),
                 "Y": Register("Y"),
                 "Z": Register("Z"),
                 }
