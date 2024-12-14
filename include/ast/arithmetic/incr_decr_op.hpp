#pragma once
#include "../node.hpp"

class postfix_incr : public node {
public:
	postfix_incr
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> postfix_expression
	):
		node(loc),
		postfix_expression_(std::move(postfix_expression)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> postfix_expression_;
};


class postfix_decr : public node {
public:
	postfix_decr
	(
		const YYLTYPE& loc , std::unique_ptr<node> postfix_expression
	):
		node(loc),
		postfix_expression_(std::move(postfix_expression)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> postfix_expression_;
};

class unary_incr : public node {
public:
	unary_incr
	(
		const YYLTYPE& loc , std::unique_ptr<node> unary_expression
	):
		node(loc),
		unary_expression_(std::move(unary_expression)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> unary_expression_;
};

class unary_decr : public node {
public:
	unary_decr
	(
		const YYLTYPE& loc , std::unique_ptr<node> unary_expression
	):
		node(loc),
		unary_expression_(std::move(unary_expression)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> unary_expression_;
};
