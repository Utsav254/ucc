#include <iostream>
#include <fstream>
#include "cli.hpp"
#include "context.hpp"
#include "error.hpp"
#include "interm_repr/interm_repr.hpp"
#include "ast/node.hpp"

CLI_args cliargs;
node *root_node;
IR *ir;
context *ctx;

int main(int argc , char **argv) {

	// initialise the basic symbol table
	ctx = new context; 

	//process cli args as required
	cliargs = parse_command_line_arguments(argc , argv);
	//open the file and emit assembly
	std::ofstream output(cliargs.outputpath , std::ios::trunc);
	if(!output.is_open()) die("Failed to open output file" , errcode::FILE_IO);

	//lex and parse the source code
	node *ast_root = parseAST(cliargs.sourcepath);
	if(ast_root == nullptr) die("Fatal parsing failure: parse tree does not exist" , errcode::INTERNAL);
	//temporarily print the ast to the console for debugging use
	root_node->printAST(1);

	//perform context traversal of AST
	
	//perform type checking and constant folding of AST
	
	//generate intermediate representation
	
	//optimisation... etc.
	
	//cleaning up before exit
	cleanup();
	output.close();	
	return 0;
}
