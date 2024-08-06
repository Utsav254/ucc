#include "ast/functions/abstract_functions.hpp"
#include <iostream>

void unamed_abstract_function_parameters::generateIR() const {
	
}

void unamed_abstract_function_parameters::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────unamed_empty_declaration" << std::endl;
	if(param_type_list_ != nullptr) param_type_list_->printAST(depth + 1);
}

void abstract_function::generateIR() const {
	
}

void abstract_function::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────abstract_function" << std::endl;
	if(direct_abstract_decl_ != nullptr) direct_abstract_decl_->printAST(depth + 1);
}

void abstract_function_parameters::generateIR() const {
	
}

void abstract_function_parameters::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────abstract_function_params" << std::endl;
	if(direct_abstract_decl_ != nullptr) direct_abstract_decl_->printAST(depth + 1);
	if(param_type_list_ != nullptr) param_type_list_->printAST(depth + 1);

}

void abstract_function_pointer::generateIR() const {
	
}

void abstract_function_pointer::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────abstract_function_pointer" << std::endl;
	if(abstract_decl_ != nullptr) abstract_decl_->printAST(depth + 1);
}

