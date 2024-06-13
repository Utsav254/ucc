#include "ast/struct_union/struct_union_decls.hpp"
#include <iostream>

void struct_declaration::generateIR() const {

}

void struct_declaration::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────struct_declaration" << std::endl;
	if(spec_qual_list_ != nullptr) spec_qual_list_->printAST(depth + 1);
	if(struct_decl_list_ != nullptr) struct_decl_list_->printAST(depth + 1);
}

void struct_declaration_list::generateIR() const {

}

void struct_declaration_list::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────struct_declaration_list"<< std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}

void struct_declarator::generateIR() const {

}

void struct_declarator::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────struct_declarator" << std::endl;
	if(declarator_ != nullptr) declarator_->printAST(depth + 1);
}

void struct_declarator_size::generateIR() const {

}

void struct_declarator_list::generateIR() const {

}

void struct_declarator_list::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────struct_declarator_list"<< std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}

void struct_declarator_size::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────struct_declarator_size" << std::endl;
	if(declarator_ != nullptr) declarator_->printAST(depth + 1);
	if(constant_expr_ != nullptr) constant_expr_->printAST(depth + 1);
}

void struct_declarator_padding::generateIR() const {

}

void struct_declarator_padding::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────struct_declarator_blank_padding" << std::endl;
	if(constant_expr_ != nullptr) constant_expr_->printAST(depth + 1);
}



