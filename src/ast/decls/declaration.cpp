#include "declaration.hpp"
#include <iostream>

void declaration::generateIR() const {

}

void declaration::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────declaration" << std::endl;
	if(declaration_specifier_ != nullptr) declaration_specifier_->printAST(depth + 1);
}

void declaration_list::generateIR() const {

}

void declaration_list::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────declaration_list"<< std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}

void init_declaration_list::generateIR() const {

}

void init_declaration_list::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────init_declaration_list"<< std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}

void declaration_init_decl::generateIR() const {

}

void declaration_init_decl::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────declaration" << std::endl;
	if(declaration_specifier_ != nullptr) declaration_specifier_->printAST(depth + 1);
	if(init_decl_list_ != nullptr) init_decl_list_->printAST(depth + 1);
}
