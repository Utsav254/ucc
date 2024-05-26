#include "switch_case.hpp"
#include <iostream>

void switch_node::generateIR() const {

}

void switch_node::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────switch_node: " << std::endl;
	if(expression_ != nullptr) expression_->printAST(depth + 1);
	if(statement_ != nullptr) statement_->printAST(depth + 1);
}

void case_default_node::generateIR() const {

}

void case_default_node::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────case_default: " << std::endl;
	if(statement_ != nullptr) statement_->printAST(depth + 1);
}

void case_node::generateIR() const {

}

void case_node::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────case_const_expr: " << std::endl;
	if(constant_expression_ != nullptr) constant_expression_->printAST(depth + 1);
	if(statement_ != nullptr) statement_->printAST(depth + 1);
}

