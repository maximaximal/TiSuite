# ast.Unsafe

Unsafe is a derived class from [ast.Function](Function). 

Unsafe blocks contain standard TiBasic code without the newly added variables and scopes of the Advanced TiBasic compiler. They serve as a compatability layer between old programs and new code, to make porting old code easier. 

If an unsafe node gets iterated through, it contains the used variables as [ast.UnsafeVariable](UnsafeVariable) nodes. 

## .content (str)

Returns the raw unsafe content of the unsafe block. 
