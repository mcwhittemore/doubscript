# Doubscript

A cli tool and C++ class for running `doub` scripts;

`doub ./script/double.doub 7`

The above runs a user script found at `./script/double.doub` and passes 7 to the first arguments of `main`.

Here is [an example](https://github.com/mcwhittemore/doubscript/blob/master/scripts/double.doub) of what that script might look like.

```
main:input // define a function that accepts one input
  print(input) // write "input: _val_of_input_" to stdout
  doubd=input*2 // multiply input by two and assign result to doubled
  print(doubd) // write "doubd: _val_of_doubd_" to stdout
```

## Langauge features

- Indentation sets scope all out whitespace is stripped before parsing.
- `//` indicates the start of a comment which continues till the end of the line.
- `print(...)` is a function that prints the name and value of the passed double to stdout
- `+-*/^=` do what you'd expect them to do.

## TODO

- `(...)` provides order of operations control
- `func(...)` calls a custom function named `func`.
- `return(...)` is a function that provides the passed value to the calling function.
- Provide standard math functions like sin, cos, log...

