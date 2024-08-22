#ifndef ABSTRACT_FUNCTIONS_HPP
#define ABSTRACT_FUNCTIONS_HPP

#include "ast/node.hpp"

class unamed_abstract_function_parameters : public node {
public:
	unamed_abstract_function_parameters(const YYLTYPE& loc , const nodelist * param_type_list) :
		node(loc) , param_type_list_(param_type_list) {}

	~unamed_abstract_function_parameters() {
		if(param_type_list_ != nullptr) delete param_type_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const nodelist *param_type_list_;
};

class abstract_function : public node {
public:
	abstract_function(const YYLTYPE& loc , const node *direct_abstract_decl):
		node(loc) , direct_abstract_decl_(direct_abstract_decl){}

	~abstract_function() {
		if(direct_abstract_decl_ != nullptr) delete direct_abstract_decl_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const node *direct_abstract_decl_;
};

class abstract_function_parameters : public abstract_function {
public:
	abstract_function_parameters(const YYLTYPE& loc , const node *direct_abstract_decl , const nodelist *param_type_list) :
		abstract_function(loc , direct_abstract_decl) , param_type_list_(param_type_list) {}

	~abstract_function_parameters() {
		if(param_type_list_ != nullptr) delete param_type_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const nodelist * param_type_list_;
};


#endif

