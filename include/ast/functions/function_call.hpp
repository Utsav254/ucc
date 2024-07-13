#ifndef FUNCTION_CALL_HPP
#define FUNCTION_CALL_HPP

#include "../node.hpp"

class function_call : public node {
public:
	function_call(const YYLTYPE&loc , const node *postfix_expr_) : 
		node(loc),
		postfix_expr_(postfix_expr_){}

	~function_call() {
		if(postfix_expr_ != nullptr) delete postfix_expr_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected: 
	const node *postfix_expr_;
};

class function_call_arg : public function_call {
public:
	function_call_arg(const YYLTYPE&loc , const node *postfix_expr ,  const nodelist *argument_expr_list) : 
		function_call(loc , postfix_expr) , 
		argument_expr_list_(argument_expr_list) {}
	~function_call_arg() {
		if(argument_expr_list_ != nullptr) delete argument_expr_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private: 
	const nodelist *argument_expr_list_;
};

class argument_expression_list : public nodelist {
public:
	argument_expression_list(const YYLTYPE&loc , node *first_node) : nodelist(loc , first_node){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

#endif
