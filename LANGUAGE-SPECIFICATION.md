# Doubscript Language Specification

Doubscript is a work in progress, for now it looks like this.

## Langauge features

- Indented lines belong to a function and unindented lines declare functions.
- `//` indicates the start of a comment which continues till the end of the line.
- `+-*/^=()` do what you'd expect them to do.
- `return(...)` returns the value in the parens to the caller.
- `function(x,y,z,...)` calls a custom function named `function` passing the args provided along.
- `<, <=, ==, >=, >` results in 0 when false and 1 when true.
- `if(...)` will run the indented lines of code directly after if the value resolved in `(...)` is 1.
- `  ` (double space) now defines different block levels and is enforced via error messages.

### TODO

- `&&` and `||`
- Formalize syntax error messages
- Provide standard math functions like sin, cos, log...
- Throw error on undefined vars at compile time
- We need arrays that can hold doubles and arrays
