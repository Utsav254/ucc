#pragma once
#include "../node.hpp"
#include "declarator.hpp"

class declaration : public node {
public:
	declaration
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> declaration_specifier
	):
		node(loc),
		declaration_specifier_(std::move(declaration_specifier)) {}
		//used in in declarating struct or union types without instantiation
		//check if struct or union present else throw warning of useless declaration
	
	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> declaration_specifier_;
};

class declaration_list : public nodelist {
public:
	declaration_list
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class init_declaration_list : public nodelist {
public:
	init_declaration_list
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}

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
	declaration_init_decl
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> declaration_specifier,
		std::unique_ptr<node> init_decl_list
	): 
		declaration(loc , std::move(declaration_specifier)),
		init_decl_list_(std::move(init_decl_list)) 
	{
		//check if the declaration specifier contains a typedef in its members
		if(declaration_specifier->decl_spec_typedef_check()) {
			init_decl_list->add_type_temp_typedef_check();
		}
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private: 
	std::unique_ptr<node> init_decl_list_;
};

