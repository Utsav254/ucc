#include "ast/struct_union_enum/enum_spec.hpp"
#include <iostream>

void enum_spec::generateIR() const {

}

void enum_spec::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────enum_spec" << std::endl;
	if(enum_list_ != nullptr) enum_list_->printAST(depth + 1);
}

void enum_spec_id::generateIR() const {

}

void enum_spec_id::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────enum_spec_id" << std::endl;
	if(identifier_ != nullptr) identifier_->printAST(depth + 1);
	if(enum_list_ != nullptr) enum_list_->printAST(depth + 1);
}

void enum_declaration::generateIR() const {

}

void enum_declaration::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────enum_declaration" << std::endl;
	if(identifier_ != nullptr) identifier_->printAST(depth + 1);
}

