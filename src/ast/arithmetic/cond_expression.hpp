#ifndef COND_EXPRESSION_HPP
#define COND_EXPRESSION_HPP

#include "../node.hpp"

class conditional_expression : public node {
public:
	conditional_expression(node *log_or_expr , node *expr , node *cond_expr) : 
		logical_or_expr_(log_or_expr) , 
		expression_(expr),
		conditional_expr_(cond_expr) {}

	~conditional_expression() {
		if(logical_or_expr_ != nullptr) delete logical_or_expr_;
		if(expression_ != nullptr) delete expression_;
		if(conditional_expr_ != nullptr) delete conditional_expr_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private: 
	node *logical_or_expr_;
	node *expression_;
	node* conditional_expr_;
};

#endif
