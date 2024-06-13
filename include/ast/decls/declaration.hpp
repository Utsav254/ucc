#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include "../node.hpp"
#include "declarator.hpp"

class declaration : public node {
public:
	declaration(node *declaration_specifier) : declaration_specifier_(declaration_specifier) {
		//do nothing these declarations are usually useless
	}
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

	void add_type_temp_typedef_check() const override {
		for(int i = 0; i < (int)nodes_.size() ; i++) {
			if(nodes_[i]->get_node_type() != typeid(init_declarator_ini)){
				nodes_[i]->add_type_temp_typedef_check();
			}
		}
	}
};

class declaration_init_decl : public declaration {
public:
	declaration_init_decl(node *declaration_specifier , nodelist *init_decl_list) : 
		declaration(declaration_specifier),
		init_decl_list_(init_decl_list) 
		{
		//check if the declaration specifier contains a typedef in its members;
		if(declaration_specifier->decl_spec_typedef_check()) {
			init_decl_list->add_type_temp_typedef_check();
		}
	}

	~declaration_init_decl() {
		if(init_decl_list_ != nullptr) delete init_decl_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private: 
	nodelist *init_decl_list_;
};

#endif
