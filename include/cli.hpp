#ifndef CLI_HPP
#define CLI_HPP

#include <string>
#include <unistd.h>

struct CLI_args {
	std::string sourcepath;
	std::string outputpath;
};

CLI_args parse_command_line_arguments(int argc , char **argv);

#endif
