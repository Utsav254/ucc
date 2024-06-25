#include <iostream>
#include "cli.hpp"
#include "error.hpp"

CLI_args parse_command_line_arguments(int argc , char **argv) {

	if((argc <= 1) || (argv[argc-1] == NULL)) {
		errors::die("No command line arguments provided");
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
				errors::die("Unable to parse commandline arguments");
				break;
		}
	}

	if(args.outputpath.length() == 0) errors::die("output file flag -o requires 1 argument");
	if(args.sourcepath.length() == 0) errors::die("source file flag -S requires 1 arugment");
	
	return args;
}

