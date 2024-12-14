#pragma once
#include "../node.hpp"

class function_call : public node {
public:
	function_call
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> postfix_expr
	): 
		node(loc),
		postfix_expr_(std::move(postfix_expr)){}

	void generateIR() const override;
	void printAST(int depth) const override;

protected: 
	std::unique_ptr<node> postfix_expr_;
};

class function_call_arg : public function_call {
public:
	function_call_arg
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> postfix_expr,
		std::unique_ptr<node> argument_expr_list
	): 
		function_call(loc , std::move(postfix_expr)) , 
		argument_expr_list_(std::move(argument_expr_list)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private: 
	std::unique_ptr<node> argument_expr_list_;
};

class argument_expression_list : public nodelist {
public:
	argument_expression_list
	(
		const YYLTYPE&loc , std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

