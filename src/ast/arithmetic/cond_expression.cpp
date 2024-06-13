#include "ast/arithmetic/cond_expression.hpp"
#include <iostream>

void conditional_expression::generateIR() const {

}

void conditional_expression::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────cond expr" << std::endl;
	if(logical_or_expr_ != nullptr) logical_or_expr_->printAST(depth + 1);
	if(expression_ != nullptr) expression_->printAST(depth + 1);
	if(conditional_expr_ != nullptr) conditional_expr_->printAST(depth + 1);
}

