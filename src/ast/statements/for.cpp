#include "for.hpp"
#include <iostream>

void for_node::generateIR() const {

}

void for_node::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────for_loop_no_mod: " << std::endl;
	if(declaration_ != nullptr) declaration_->printAST(depth + 1);
	if(condition_expr_ != nullptr) condition_expr_->printAST(depth + 1);
	if(statement_ != nullptr) statement_->printAST(depth + 1);
}

void for_node_mod::generateIR() const {

}

void for_node_mod::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────for_loop: " << std::endl;
	if(declaration_ != nullptr) declaration_->printAST(depth + 1);
	if(condition_expr_ != nullptr) condition_expr_->printAST(depth + 1);
	if(modifying_expr_ != nullptr) modifying_expr_->printAST(depth + 1);
	if(statement_ != nullptr) statement_->printAST(depth + 1);
}

void for_node_ext::generateIR() const {

}

void for_node_ext::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────for_loop_ext_decl_no_mod: " << std::endl;
	if(initial_expr_ != nullptr) initial_expr_->printAST(depth + 1);
	if(condition_expr_ != nullptr) condition_expr_->printAST(depth + 1);
	if(statement_ != nullptr) statement_->printAST(depth + 1);
}

void for_node_ext_mod::generateIR() const {

}

void for_node_ext_mod::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────for_loop_ext_decl: " << std::endl;
	if(initial_expr_ != nullptr) initial_expr_->printAST(depth + 1);
	if(condition_expr_ != nullptr) condition_expr_->printAST(depth + 1);
	if(modifying_expr_ != nullptr) modifying_expr_->printAST(depth + 1);
	if(statement_ != nullptr) statement_->printAST(depth + 1);
}

