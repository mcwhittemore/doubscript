# Doubscript

C++ headerfile for running `doubscript` programs.

For a program to run doubscripts from the CLI, see [doub](https://github.com/mcwhittemore/doub).

## Usage

### doub::Doubscript

This is the entry point class for Doubscript.

**About the constructor**

This constructor takes `content` representing a `doubscript` program and processes it. If there are syntax errors in the program, creating this will throw an error.

- content {`std::string`} - a `doublescript` program

### doub::Doubscript::run

Runs the provided function from the loaded program, passing along the provided args.

- f {`std::string`} - the name of the function to run
- args {`std::vector<double>`} - the vales of the functions arguments
- returns {`double`}

### doub::Doubscript::debug

Same as `doub::Doubscipt::run` except that it prints a detailed debug list of what vars and values are being used through out the running of the program.

- f {`std::string`} - the name of the function to run
- args {`std::vector<double>`} - the vales of the functions arguments
- stream {`std::ostream`} [optional] - a stream to write the debug logs to. Will default to `std::cout`.
- returns {`double`}

### doub::Doubscript::getProgram

Returns the `std::string` content passed to the constructor.

- returns {`std::string`}

### doub::Doubscript::fromFile

_static_

Takes a file path and returns a new Doubscript program.

- file {`std::string`} - the path to the file from the cwd.
- returns {`doub::Doubscript`}

