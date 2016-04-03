Taglist
=======

All the standard tags from the calculator are still active. This compiler includes 
some additional tags to simplify development of complex applcations with interop 
capabilities between each other.

return
------

Synopsis: `return <variable>`

Returns a value (only the same type as the function declaration says) from a function. 

function
--------

Synopsis: `function <function name>(<param type> <param name>, <param type 2> <param name 2>, ...) : <return type>`

```
//Normal function
function funcName(num paramA, num paramB) : num
{
    return paramA + paramB;
}

//Function with unsafe body
function unsafeFunction(num a, num b) : num
{
    a * b->b;
    return b;
}
```

program
-------

Synopsis: `program programName()`

A program is an entry on the calculators program list. These are the real entry points!

To call a function or do anything with this language, you have to define entry points using this `program` tag. The name is going to be converted into CAPS. 

comments
--------

Synopsis: `// comment`

Comments are not compiled and can contain additional program information. 

unsafe (Block)
--------------

Synopsis: `unsafe (varA : A, varB : B) {  }`

```
unsafe unsafeName(varA : A, varB : B)
{
    2->A
    8->B
    A*B->L
}
```

unsafe (include)
----------------

Synopsis: `unsafe (varA : A, varB : B) "filename.82a"`

```
unsafe unsafeName(varA : A, varB : B) "filename.82a"
```
