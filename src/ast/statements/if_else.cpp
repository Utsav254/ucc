#include "ast/statements/if_else.hpp"
#include <iostream>

void if_node::generateIR() const {

}

void if_node::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────if_node: " << std::endl;
	if(expression_ != nullptr) expression_->printAST(depth + 1);
	if(if_body_ != nullptr) if_body_->printAST(depth + 1);
}

void if_else_node::generateIR() const {

}

void if_else_node::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────if_else_node: " << std::endl;
	if(expression_ != nullptr) expression_->printAST(depth + 1);
	if(if_body_ != nullptr) if_body_->printAST(depth + 1);
	if(else_body_ != nullptr) else_body_->printAST(depth + 1);
}

