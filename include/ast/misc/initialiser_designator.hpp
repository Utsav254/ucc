#pragma once
#include "ast/node.hpp"

class designator_identifier : public node {
public:
	designator_identifier
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> identifier
	):
		node(loc) , identifier_(std::move(identifier)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> identifier_;
};

class designator_constant_expr : public node {
public:
	designator_constant_expr
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> constant_expr
	):
		node(loc) , constant_expr_(std::move(constant_expr)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> constant_expr_;
};

class designator_list : public nodelist {
public:
	designator_list
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class designation : public node {
public:
	designation
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> designator_list,
		std::unique_ptr<node> initialiser
	):
		node(loc),
		designator_list_(std::move(designator_list)),
		initialiser_(std::move(initialiser)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node>  designator_list_;
	std::unique_ptr<node>  initialiser_;
};

class initialiser_list : public nodelist {
public:
	initialiser_list
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class initialiser : public node {
public:
	initialiser
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> initialiser_list
	):
		node(loc) , initialiser_list_(std::move(initialiser_list)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> initialiser_list_;
};


