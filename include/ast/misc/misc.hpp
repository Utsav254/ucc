#pragma once
#include "../node.hpp"

class empty : public node {
public:
	empty(const YYLTYPE& loc) : node(loc){}
	~empty(){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class ellipsis : public node {
public:
	ellipsis(const YYLTYPE& loc) : node(loc){}
	~ellipsis(){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class sizeof_node : public node {
public:
	sizeof_node
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> unary_expression
	):
		node(loc), unary_expression_(std::move(unary_expression)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> unary_expression_;
};

class sizeof_node_type : public node {
public:
	sizeof_node_type
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> type_name
	):
		node(loc),
		type_name_(std::move(type_name)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> type_name_;
};

class translation_unit : public nodelist {
public:
	translation_unit
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class unamed_empty_declaration : public node {
public:
	unamed_empty_declaration
	(
		const YYLTYPE& loc
	):
		node(loc) {}

	void generateIR() const override;	
	void printAST(int depth) const override;
};

