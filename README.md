# Dubscript

A cli tool and C++ class for running `dbs` scripts;

`dbs ./script/dbl --args=7`

The above runs a user script and passes 7 to it as `args[0]`.

**What is an dbs script**

```
func: arg
  left = right
  val = 2 * 2;
  print(val) // => "val: 4"
  return(val);
```

- Indentation sets scope all out whitespace is stripped before parsing.
- `//` indicates the start of a comment which continues till the end of the line.
- There are functions, doubles and arrays which can contain arrays or doubles.
- `return` is a function that provides the passed value to the calling function.
- `print` is a function that prints the name and value of the passed double to stdout

