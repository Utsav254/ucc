#include "ast/statements/while.hpp"
#include <iostream>

void while_node::generateIR() const {

}

void while_node::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────while_loop: " << std::endl;
	if(expression_ != nullptr) expression_->printAST(depth + 1);
	if(statement_ != nullptr) statement_->printAST(depth + 1);
}

void do_while_node::generateIR() const {

}

void do_while_node::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────do_while_loop: " << std::endl;
	if(statement_ != nullptr) statement_->printAST(depth + 1);
	if(expression_ != nullptr) expression_->printAST(depth + 1);
}

