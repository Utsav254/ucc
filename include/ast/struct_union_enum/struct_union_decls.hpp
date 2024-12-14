#pragma once
#include "../node.hpp"

class struct_declaration : public node {
public:
	struct_declaration
	(
		const YYLTYPE& loc,
		std::unique_ptr<nodelist> spec_qual_list,
		std::unique_ptr<nodelist> struct_decl_list
	):
		node(loc),
		spec_qual_list_(std::move(spec_qual_list)),
		struct_decl_list_(std::move(struct_decl_list)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> spec_qual_list_;
	std::unique_ptr<node> struct_decl_list_;
};

class struct_declaration_list : public nodelist {
public:
	struct_declaration_list
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class struct_declarator : public node {
public:
	struct_declarator
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> declarator
	):
		node(loc),
		declarator_(std::move(declarator)){}


	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> declarator_;
};

class struct_declarator_list : public nodelist {
public:
	struct_declarator_list
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class struct_declarator_size : public struct_declarator {
public:
	struct_declarator_size
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> declarator,
		std::unique_ptr<node> constant_expr
	):
		struct_declarator(loc , std::move(declarator)),
		constant_expr_(std::move(constant_expr)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> constant_expr_;
};

class struct_declarator_padding : public node {
public:
	struct_declarator_padding
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> constant_expr
	):
		node(loc),
		constant_expr_(std::move(constant_expr)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> constant_expr_;
};


