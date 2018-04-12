# Changelog

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

