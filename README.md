## UCC: Upsilon C Compiler
A simple c99 compiler.

Things to consider:
    - global vars need fixing
    - better type system: const string referencing?
    - smart pointers?
    - might have to add a function table which hold function name and function info:
        - function trace
        - function stack frame
        - return type
    - add support for multi line string declaration
    - use c strings in some places ... const char *s for string literals speed optimisation?

Things to ammend later:
    - exit code on errors should be reconsidered
    - locations: handle how nodelist->pushback handles location ...



