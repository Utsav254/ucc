#include "ast/decls/abstract_declarator.hpp"
#include <iostream>

void abstract_declarator::generateIR() const {

}

void abstract_declarator::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────abstract_declarator" << std::endl;
	if(abstract_direct_decl_ != nullptr) abstract_direct_decl_->printAST(depth + 1);
}


void abstract_declarator_pointer::generateIR() const {

}

void abstract_declarator_pointer::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────abstract_declarator_pointer" << std::endl;
	if(pointer_ != nullptr) pointer_->printAST(depth + 1);
	if(abstract_direct_decl_ != nullptr) abstract_direct_decl_->printAST(depth + 1);
}


