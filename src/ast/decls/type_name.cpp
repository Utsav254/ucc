#include "ast/decls/type_name.hpp"
#include <iostream>

void type_name::generateIR() const {

}

void type_name::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────type_name" << std::endl;
	if(spec_qual_list_ != nullptr) spec_qual_list_->printAST(depth + 1);
}


void type_name_abstract::generateIR() const {

}

void type_name_abstract::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────type_specifier: " << std::endl;
	if(spec_qual_list_ != nullptr) spec_qual_list_->printAST(depth + 1);
	if(abstract_decl_ != nullptr) abstract_decl_->printAST(depth + 1);
}


