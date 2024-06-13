#ifndef ERROR_HPP
#define ERROR_HPP

#include "ast/node.hpp"
#include "cli.hpp"
#include "context.hpp"
#include "interm_repr/interm_repr.hpp"
#include <string>

extern int errlineno;
extern std::string errpadding;
extern CLI_args cliargs;

// to be delete by cleanup
extern node *rootnode;
extern IR *ir;
extern context *ctx;

enum class errcode {
	COMMAND_LINE_ARGS = 1,
	FILE_IO,
	SYNTAX,
	PARSING,
	INTERNAL,
};

const char* err_to_string(errcode e); 

void die(std::string errmsg , errcode errcd);

void cleanup();

#endif


