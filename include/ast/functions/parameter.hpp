#pragma once
#include "../node.hpp"

class parameter_decl : public node {
public:
	parameter_decl
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> declaration_specifier
	):
		node(loc),
		declaration_specifier_(std::move(declaration_specifier)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> declaration_specifier_;
};

class parameter_full_decl : public parameter_decl {
public:
	parameter_full_decl
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> declaration_specifier,
		std::unique_ptr<node> declarator
	):
		parameter_decl(loc , std::move(declaration_specifier)),
		declarator_(std::move(declarator)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private: 
	std::unique_ptr<node> declarator_;
};

class parameter_decl_abstract : public parameter_decl {
public:
	parameter_decl_abstract
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> declaration_specifier,
		std::unique_ptr<node> abstract_declarator
	):
		parameter_decl(loc , std::move(declaration_specifier)),
		abstract_declarator_(std::move(abstract_declarator)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private: 
	std::unique_ptr<node> abstract_declarator_;
};

class parameter_list : public nodelist {
public:
	parameter_list
	(
		const YYLTYPE& loc , std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class variadic_parameter : public node {
public:
	variadic_parameter
	(
		const YYLTYPE& loc , std::unique_ptr<node> parameter_list
	):
		node(loc),
		parameter_list_(std::move(parameter_list)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> parameter_list_;
};

