#pragma once
#include "../node.hpp"

class jump_statement_goto : public node {
public:
	jump_statement_goto
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> identifier
	):
		node(loc),
		identifier_(std::move(identifier)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> identifier_;
};

class jump_statement_continue : public node {
public:
	jump_statement_continue(const YYLTYPE&loc) : node(loc) {}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class jump_statement_break : public node {
public:
	jump_statement_break(const YYLTYPE&loc) : node(loc) {}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class jump_statement_ret : public node {
public:
	jump_statement_ret(const YYLTYPE&loc) : node(loc) {}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class jump_statement_ret_expr: public node {
public:
	jump_statement_ret_expr
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> expression
	):
		node(loc),
		expression_(std::move(expression)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> expression_;
};

class goto_target : public node {
public:
	goto_target
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> identifier,
		std::unique_ptr<node> statement
	):
		node(loc),
		identifier_(std::move(identifier)),
		statement_(std::move(statement)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> identifier_;
	std::unique_ptr<node> statement_;
};

