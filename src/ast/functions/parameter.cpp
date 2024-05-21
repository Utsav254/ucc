#include "parameter.hpp"
#include <iostream>

void parameter_decl::generateIR() const {

}

void parameter_decl::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────trace param decl" << std::endl;
	if(declaration_specifier_ != nullptr) declaration_specifier_->printAST(depth + 1);
}

void parameter_full_decl::generateIR() const {

}

void parameter_full_decl::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────parameter declaration" << std::endl;
	if(declaration_specifier_ != nullptr) declaration_specifier_->printAST(depth + 1);
	if(declarator_ != nullptr) declarator_->printAST(depth + 1);
}
