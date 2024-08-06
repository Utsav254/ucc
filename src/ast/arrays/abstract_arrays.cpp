#include "ast/arrays/abstract_arrays.hpp"
#include <iostream>

void unamed_empty_array::generateIR() const {
	
}

void unamed_empty_array::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────abstract_decl_array" << std::endl;
}

void unamed_empty_array_size::generateIR() const {

}

void unamed_empty_array_size::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────abstract_decl_array_size" << std::endl;
	if(assignment_expr_ != nullptr) assignment_expr_->printAST(depth + 1);
}

void array_decl_abstract::generateIR() const {

}

void array_decl_abstract::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────array_definition" << std::endl;
	if(direct_abstract_decl_ != nullptr) direct_abstract_decl_->printAST(depth + 1);
}

void array_decl_abstract_size::generateIR() const {

}

void array_decl_abstract_size::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────array_definition" << std::endl;
	if(direct_abstract_decl_ != nullptr) direct_abstract_decl_->printAST(depth + 1);
	if(assignment_expr_ != nullptr) assignment_expr_->printAST(depth + 1);
}

