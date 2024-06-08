## UCC: Upsilon C Compiler
A simple c99 compiler.

### NOTES:
Lexing and parsing are handled by flex and bison... the result is an abstract syntax tree which holds all the information...

    -to handle any typedef... need to add features to the declaration constructor which performs some type checking within it own AST
    -then add any typedefinitions to the type table
    -add any variable declarations with only some of the information to the symbol table

    -but also keep in mind that scopes must be tracked since typedefs have scopes and with scope information also populate the symbol table
    -scopes start when there is a compound statement ... need to give each compound statent a name --- function name? if/else/while/for etc

This parse tree must be traversed to populate the symbol table (aka context)

Traverse the tree again to convert into intermediate representation:

    -this should include functional blocks such as function boilerplate: prologue, epilogues with stackframe size speicifed
    -jump or gotos to handle the control flow statements
    -three address code to handle the main body of the code being compiled

These would all be linked together using some sort of graph
The TAC sections will also be optimized using directed acyclic graph theory not sure how this works as of yet??

The IR should be enough to then compile to the target assembly language x86? riscV? to be solved later or 

    -might have to consider graph colouring algorithms (greedy or something?)

The IR would probably made using a base class called "block" from which there are derrived classes for each block type from above


### TODO:
    
    1> custom types using typedef
    2> write testing script for parsing only? reuse test from langproc ?
    3> integration with context




