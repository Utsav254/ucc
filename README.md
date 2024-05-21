## UCC
A simple c99 compiler.

### NOTES:
Lexing and parsing are handled by flex and bison... the result is an abstract syntax tree which holds all the information...

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
    
    1> add some parsing grammar rules to yacc file...
    2> implement more sophisticated clean up system...when there is an error, there are random nodes which arent owned my any object and dont get freed

