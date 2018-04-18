# Changelog

## 0.5.0

- Fixes code indentation requirements bug to require two spaces for all lines in a function and two more spaces per block depth.
- Drops `\t` indentation support.

### Language Features

- `if(...)` is now supported and will run the directly indented block of code below it if the final value resolved in `(...)` resolves to 1. The run block will share the scope of the function. 

## 0.4.0

### Language Features

- `<, <=, ==, >=, >` opperations will now result in 0 when its wrong and 1 when its right

## 0.3.1

- Fix bug where `return(func(1,2))` would segfault
- Adds test coverage for maths and calling functions

## 0.3.0

### Header API

- Add `doub::Doubscript::debug` to run a sprint and log our debug information

### Language Features

- Drops `print(...)` from the langauge

## 0.2.0

### Header API

- Changes `doub::Doubscript::run` to return a double

### Language Features

- Adds `()`
- Adds `return()`
- Adds `function()`

## 0.1.0

The initial version!

### Language Features

- Indentation sets scope all out whitespace is stripped before parsing.
- `//` indicates the start of a comment which continues till the end of the line.
- `print(...)` is a function that prints the name and value of the passed double to stdout
- `+-*/^=` do what you'd expect them to do.

