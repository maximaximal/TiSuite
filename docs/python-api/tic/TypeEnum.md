# tic.TypeEnum

The TypeEnum is a number representation of all available types. 

The following table represents all available values in this enumeration. 

TypeEnum | Name of the Type | Description | Short Form in TiC
-------- | ---------------- | ----------- | -----------------
.Number | Number | A normal number on the calculator. | "num"
.Matrix | Matrix | A normal matrix (2D-array) on the calculator | "mat"
.List | List | A normal list (1D-array) on the calculator | "lst"
.String | String | A normal string (Str0-Str6) on the calculator | "str"
.Unknown | Unknown | An unknown type (can come from unsafe blocks) | - (Compiler Internal)
.No_Type | No Type | An error in the AST | - (Compiler Interna)
