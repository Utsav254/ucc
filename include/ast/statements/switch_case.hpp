#pragma once
#include "../node.hpp"

class switch_node : public node {
public:
	switch_node
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

private:
	std::unique_ptr<node> expression_;
	std::unique_ptr<node> statement_;
};

class case_default_node : public node {
public:
	case_default_node
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> statement
	):
		node(loc),
		statement_(std::move(statement)){}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> statement_;
};

class case_node : public case_default_node {
public:
	case_node
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> statement,
		std::unique_ptr<node> constant_expression
	): 
		case_default_node(loc , std::move(statement)),
		constant_expression_(std::move(constant_expression)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> constant_expression_;
};

