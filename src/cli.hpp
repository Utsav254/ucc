#ifndef CLI_HPP
#define CLI_HPP

#include <string>
#include <unistd.h>

extern int err_column;

enum class errcode {
	COMMAND_LINE_ARGS = 1,
	FILE_IO,
	SYNTAX,
	PARSING,
};


const char* err_to_string(errcode e);

//error message
//exit error code
void die(std::string message , errcode n);

void cleanup();

struct CLI_args {
	std::string sourcepath;
	std::string outputpath;
};

CLI_args parse_command_line_arguments(int argc , char **argv);

#endif
