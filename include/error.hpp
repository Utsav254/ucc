#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <fstream>

#include "ast/node.hpp"
#include "ast/locations.hpp"
#include "interm_repr/interm_repr.hpp"

extern node *rootnode;
extern IR *ir;

class error {
public:
	error(const YYLTYPE&loc, const std::string msg , const bool is_warning) : 
		message_(msg),
		is_warning_(is_warning) , loc_(loc){}

	~error() = default;

	void emit_err(std::ifstream& in) const ;
	bool check_warning() const {return is_warning_;}
private:
	const std::string message_;
	const bool is_warning_;
	const YYLTYPE loc_;
};


namespace errors {
	
	void add_err(const error *err);
	int get_err_count();
	void emit_all_err(std::ifstream& in);
	
	//---- fatal functions -----//
	void die(const std::string errmsg);
	void cleanup();
}

#endif


