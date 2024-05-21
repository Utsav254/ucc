#include <iostream>
#include <fstream>
#include "cli.hpp"
#include "interm_repr/interm_repr.hpp"
#include "ast/node.hpp"

node *root_node;
IR *ir;

int main(int argc , char **argv) {

	//process cli args as required
	CLI_args args = parse_command_line_arguments(argc , argv);

	//open the file and emit assembly
	std::ofstream output(args.outputpath , std::ios::trunc);
	if(!output.is_open()) die("Failed to open output file" , errcode::FILE_IO);

	node *ast_root = parseAST(args.sourcepath);

	if(ast_root == nullptr) die("Fatal parsing failure: parse tree does not exist" , errcode::PARSING);

	//temporarily print the ast to the console for debugging use
	root_node->printAST(1);
	
	//cleaning up before exit
	cleanup();
	output.close();	
	return 0;
}
