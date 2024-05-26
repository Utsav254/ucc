#include "function_call.hpp"
#include <iostream>

void function_call::generateIR() const {

}

void function_call::printAST(int depth) const{ 
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────function_call" << std::endl;
	if(postfix_expr_ != nullptr) postfix_expr_->printAST(depth + 1);

}

void function_call_arg::generateIR() const {

}

void function_call_arg::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────function_call_arg" << std::endl;
	if(postfix_expr_ != nullptr) postfix_expr_->printAST(depth + 1);
	if(argument_expr_list_ != nullptr) argument_expr_list_->printAST(depth + 1);
}
