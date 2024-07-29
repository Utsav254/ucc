## UCC: Upsilon C Compiler
A simple c99 compiler.

Things to consider:

    - the use of the { token marks the start of a scope
        - create a temp scope stack to manage scopes while scanning and parsing ... scopes can be unnamed ...
        - further type checking will be carried later anyways
        - useful to sorting errors such as :

            typedef int i32;
            i32 i32 = 5;
                ~~~ exception added for this case since the previous token was a typename 
                    safe to assume that this is intended to be an identifier

            return i32;
                   ~~~ however here this would be a type name which ends up throwing an error ...
                       might be useful to maintain a set of variables which are in scope;

    - the use of } marks the end of the scope

Things to ammend later:
    - exit code on errors should be reconsidered
    - multi line string

Performance:
    - string use in types, is there a better way?
    - better hashes for std::maps ?


