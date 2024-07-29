#include "ast/struct_union_enum/enumerator.hpp"
#include <iostream>

void enumerator_list::generateIR() const {

}

void enumerator_list::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────enumerator_list"<< std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}

void enumerator::generateIR() const {

}

void enumerator::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────enumerator"<< std::endl;
	if(identifier_ != nullptr) identifier_->printAST(depth + 1);
}

void enumerator_const_expr::generateIR() const {

}

void enumerator_const_expr::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────enumerator_cons_expr"<< std::endl;
	if(identifier_ != nullptr) identifier_->printAST(depth + 1);
	if(const_expr_ != nullptr) const_expr_->printAST(depth + 1);
}

