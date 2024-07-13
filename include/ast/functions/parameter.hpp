#ifndef PARAMETER_HPP
#define PARAMETER_HPP

#include "../node.hpp"

class parameter_decl : public node {
public:
	parameter_decl(const YYLTYPE& loc , const node *declaration_specifier) :
		node(loc),
		declaration_specifier_(declaration_specifier) {}

	~parameter_decl() {
		if(declaration_specifier_ != nullptr) delete declaration_specifier_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const node *declaration_specifier_;
};

class parameter_full_decl : public parameter_decl {
public:
	parameter_full_decl(const YYLTYPE& loc , const node *declaration_specifier , const node *declarator) :
		parameter_decl(loc , declaration_specifier),
		declarator_(declarator) {}

	~parameter_full_decl() {
		if(declarator_ != nullptr) delete declarator_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private: 
	const node *declarator_;
};

class parameter_list : public nodelist {
public:
	parameter_list(const YYLTYPE& loc , node *first_node) : nodelist(loc , first_node){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class variadic_parameter : public node {
public:
	variadic_parameter(const YYLTYPE& loc , const nodelist *parameter_list):
		node(loc),
		parameter_list_(parameter_list){}

	~variadic_parameter() {
		if(parameter_list_ != nullptr) delete parameter_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const nodelist *parameter_list_;
};

#endif
