# Doubscript Language Specification

Doubscript is a work in progress.

## Goals

Doubscript aims to empower application developers the ability to add 

## Langauge features

- Indented lines belong to a function and thus unindented lines declare functions.
- `//` indicates the start of a comment which continues till the end of the line.
- `print(var)` is a function that prints the name and value of the passed double to stdout
- `return(...)` stops the functions exicution and sends the value of its expression to the parent program or function
- `+-*/^=()` do what you'd expect them to do.

### TODO

- Formalize syntax error messages
- `(...)` provides order of operations control
- `func(...)` calls a custom function named `func`.
- `return(...)` is a function that provides the passed value to the calling function.
- Provide standard math functions like sin, cos, log...
- Provide good parsing errors
- Throw error on undefined vars at compile time
- We need arrays that can hold doubles and arrays
- Program wide vars (aka, globals)
