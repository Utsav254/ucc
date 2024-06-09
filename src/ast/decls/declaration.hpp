#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include "../node.hpp"

class declaration : public node {
public:
	declaration(node *declaration_specifier) : declaration_specifier_(declaration_specifier) {}
	~declaration() {
		if(declaration_specifier_ != nullptr) delete declaration_specifier_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	node *declaration_specifier_;
};

class declaration_list : public nodelist {
public:
	declaration_list(node *first_node) : nodelist(first_node){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class init_declaration_list : public nodelist {
public:
	init_declaration_list(node *first_node) : nodelist(first_node){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class declaration_init_decl : public declaration {
public:
	declaration_init_decl(node *declaration_specifier , nodelist *init_decl_list) : 
		declaration(declaration_specifier),
		init_decl_list_(init_decl_list) {}
	~declaration_init_decl() {
		if(init_decl_list_ != nullptr) delete init_decl_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private: 
	nodelist *init_decl_list_;
};

#endif
