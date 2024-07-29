#include "ast/decls/casting.hpp"
#include <iostream>

void cast_expression::generateIR() const {

}

void cast_expression::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────cast_expression" << std::endl;
	if(type_name_ != nullptr) type_name_->printAST(depth + 1);
	if(cast_expression_ != nullptr) cast_expression_->printAST(depth + 1);
}

void cast_compound_literal::generateIR() const {

}

void cast_compound_literal::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────casting_compound_literal" << std::endl;
	if(type_name_ != nullptr) type_name_->printAST(depth + 1);
	if(init_list_ != nullptr) init_list_->printAST(depth + 1);
}
