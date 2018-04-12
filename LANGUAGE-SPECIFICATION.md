# Doubscript Language Specification

Doubscript is a work in progress.

## Langauge features

- Indented lines belong to a function and thus unindented lines declare functions.
- `//` indicates the start of a comment which continues till the end of the line.
- `+-*/^=()` do what you'd expect them to do.
- `return(...)` returns the value in the parens to the caller
- `function(x,y,z,...)` calls a custom function named `function` passing the args provided along.

### TODO

- logicly built doubles
  - `0 < 1 => 1`
  - `0 > 1 => 0`
  - `0 = 1 => 0`
  - `0 <= 1 => 1`
  - `0 >= 1 => 0`
- `if` and `while` for basic processing control
- Formalize syntax error messages
- Provide standard math functions like sin, cos, log...
- Provide good parsing errors
- Throw error on undefined vars at compile time
- We need arrays that can hold doubles and arrays
- Program wide vars (aka, globals)
