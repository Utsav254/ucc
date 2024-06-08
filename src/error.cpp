#include "error.hpp"
#include <iostream>
#include <fstream>

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
	std::cerr << "\x1b[31mERROR:\x1b[0m " << err_to_string(n) << "\n";

	switch(n) {
		case errcode::COMMAND_LINE_ARGS:
		case errcode::FILE_IO:
		case errcode::INTERNAL: 
			std::cerr << message << std::endl;
			break;
        case errcode::SYNTAX:
		case errcode::PARSING: {
			std::ifstream file(cliargs.sourcepath);
			std::string line;
			int currline = 1;
			while(std::getline(file , line)){
				if(currline == (errlineno+1)) {
					std::cerr << " " << errlineno+1 << "|";
					std::cerr << line << std::endl;
					std::cerr << "  " << "|";
					std::cerr << errpadding << "^" << std::endl;
					break;
				}
				else currline++;
			}
        	break;
		}
		default: 
			std::cerr << "Unknown" << std::endl;
    }

    cleanup();

	exit((int)n);
}

void cleanup() {
	if (root_node != nullptr) delete root_node;
	if (ir != nullptr) delete ir;
}


