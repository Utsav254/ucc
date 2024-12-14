#pragma once
#include "../node.hpp"

class while_node : public node {
public:
	while_node
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> expression,
		std::unique_ptr<node> statement
	):
		node(loc),
		expression_(std::move(expression)),
		statement_(std::move(statement)){}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> expression_;
	std::unique_ptr<node> statement_;
};

class do_while_node : public while_node {
public:
	do_while_node
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> statement,
		std::unique_ptr<node> expression
	):
		while_node(loc , std::move(expression), std::move(statement)){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

