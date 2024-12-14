#pragma once
#include "../node.hpp"

class array_index : public node {
public:
	array_index
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> postfix_expr,
		std::unique_ptr<node> expr
	):
		node(loc),
		postfix_expr_(std::move(postfix_expr)) , expr_(std::move(expr)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> postfix_expr_;
	std::unique_ptr<node> expr_;
};

