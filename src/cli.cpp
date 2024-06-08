#include <iostream>
#include "cli.hpp"
#include "error.hpp"

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

