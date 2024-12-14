#pragma once
#include "../node.hpp"

class conditional_expression : public node {
public:
	conditional_expression
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> log_or_expr,
		std::unique_ptr<node> expr,
		std::unique_ptr<node> cond_expr
	): 
		node(loc),
		logical_or_expr_(std::move(log_or_expr)), 
		expression_(std::move(expr)),
		conditional_expr_(std::move(cond_expr)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private: 
	std::unique_ptr<node> logical_or_expr_;
	std::unique_ptr<node> expression_;
	std::unique_ptr<node>  conditional_expr_;
};
