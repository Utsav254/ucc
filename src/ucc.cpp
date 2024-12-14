#include <iostream>
#include <fstream>
#include "cli.hpp"
#include "context/context.hpp"
#include "error.hpp"
#include "interm_repr/interm_repr.hpp"
#include "ast/node.hpp"

//global pointers to structures
std::unique_ptr<node> root_node;
IR *ir;

int main(int argc , char **argv) {

	//initialise the compiler:
	CLI_args cliargs;
	context::initialise();

	//process cli args as required
	cliargs = parse_command_line_arguments(argc , argv);
	//open the file and emit assembly
	std::ofstream output(cliargs.outputpath , std::ios::trunc);
	if(!output.is_open()) errors::die("Failed to open output file");

	//lex and parse the source code
	std::unique_ptr<node> ast_root = parseAST(cliargs.sourcepath);
	if(ast_root == nullptr) errors::die("Fatal parsing failure: parse tree does not exist");

	//temporarily print the ast to the console for debugging use
	root_node->printAST(1);

	//perform context traversal of AST
	
	//perform type checking and constant folding of AST
	
	//ready to check for errors:
	std::ifstream temp(cliargs.sourcepath);
	errors::emit_all_err(temp);

	if(errors::get_err_count()) {
		errors::die("got errors - will terminate compilation");
	}
	
	//generate intermediate representation
	
	//optimisation... etc.
	
	//cleaning up before exit
	errors::cleanup();
	output.close();	
	return 0;
}
