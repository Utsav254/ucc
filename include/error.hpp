#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>

#include "ast/node.hpp"
#include "cli.hpp"
#include "interm_repr/interm_repr.hpp"

extern CLI_args cliargs;
extern node *rootnode;
extern IR *ir;

class error {
public:
	error(std::string msg , bool is_warning) : 
		message_(msg) , is_warning_(is_warning){}
	virtual ~error(){}
	virtual void emit_err() const = 0;

	bool check_warning() {return is_warning_;}
protected:
	std::string message_;
	bool is_warning_;
};

namespace errors {
	
	void add_err(error *err);
	int get_err_count();
	void emit_all_err();
	
	//---- fatal functions -----//
	void die(std::string errmsg);
	void cleanup();
}

#endif


