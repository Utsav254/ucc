#include "ast/functions/parameter.hpp"
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


void parameter_decl_abstract::generateIR() const {

}

void parameter_decl_abstract::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────parameter declaration_abstract" << std::endl;
	if(declaration_specifier_ != nullptr) declaration_specifier_->printAST(depth + 1);
	if(abstract_declarator_ != nullptr) abstract_declarator_->printAST(depth + 1);
}

void parameter_list::generateIR() const {

}

void parameter_list::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────parameter_list"<< std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}

void variadic_parameter::generateIR() const {

}

void variadic_parameter::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────variadic_parameter" << std::endl;
	if(parameter_list_ != nullptr) parameter_list_->printAST(depth + 1);
}



