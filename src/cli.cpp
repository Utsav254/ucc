#include <iostream>
#include "cli.hpp"
#include "ast/node.hpp"
#include "interm_repr/interm_repr.hpp"

const char* err_to_string(errcode e) {
	switch(e) {
		case errcode::COMMAND_LINE_ARGS: return "command line args";
		case errcode::FILE_IO: return "file I/O";
		case errcode::SYNTAX: return "syntax";
		case errcode::PARSING: return "parsing";
		case errcode::INTERNAL: return "internal";
		default: return "unknown";
	}
}	

void die(std::string message , errcode n) {
	std::string spaces(err_column , ' ');
	std::cerr << "\x1b[31mERROR:\x1b[0m " << err_to_string(n) << "\n";

	switch(n) {
		case errcode::COMMAND_LINE_ARGS:
		case errcode::FILE_IO:
			std::cerr << message << std::endl;
			break;
        case errcode::SYNTAX:
			//output the string and give the indicator of where the error occured
			std::cerr << message << std::endl;
			std::cerr << spaces << "^" << std::endl; 
			break;
		case errcode::PARSING:
			std::cerr << "No abtract syntax tree was made...possible that root node == nullptr" << std::endl;
        	break;
		case errcode::INTERNAL: 
			std::cerr << message << std::endl;
			break;
		default: 
			std::cerr << "Unknown" << std::endl;
			break;
    }

    cleanup();

	exit((int)n);
}

void cleanup() {
	if (root_node != nullptr) delete root_node;
	if (ir != nullptr) delete ir;
}

CLI_args parse_command_line_arguments(int argc , char **argv) {

	if((argc <= 1) || (argv[argc-1] == NULL)) {
		die("No command line arguments provided" , errcode::COMMAND_LINE_ARGS);
	}

	CLI_args args;

	opterr = 0;	
	int opt;
	while((opt = getopt(argc , argv , "o:S:")) != -1) {
		switch(opt) {
			case 'o':
				args.outputpath = std::string(optarg);
				break;	
			case 'S':
				args.sourcepath = std::string(optarg);
				break;
			case '?':
			default:
				if(optopt == 'S' || optopt == 'o') std::cerr << "flag: " << optopt << "requires an argument" << std::endl;
				else if(isprint(optopt)) std::cerr << "Unknown flag: " << (char)optopt << std::endl;
				else std::cerr << "Unknown flag character" << std::endl;
				die("Unable to parse commandline arguments" , errcode::COMMAND_LINE_ARGS);
				break;
		}
	}

	if(args.outputpath.length() == 0) die("output file flag -o requires 1 argument" , errcode::COMMAND_LINE_ARGS);
	if(args.sourcepath.length() == 0) die("source file flag -S requires 1 arugment" , errcode::COMMAND_LINE_ARGS);
	
	return args;
}

