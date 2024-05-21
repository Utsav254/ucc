#include "function_declarator.hpp"
#include <iostream>

void function_declarator::generateIR() const {

}

void function_declarator::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────function_declarator" << std::endl;
	if(direct_declarator_ != nullptr) direct_declarator_->printAST(depth + 1);
}

void function_declarator_param::generateIR() const {

}

void function_declarator_param::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────function declarator param" << std::endl;
	if(direct_declarator_ != nullptr) direct_declarator_->printAST(depth + 1);
	if(parameter_list_ != nullptr) parameter_list_->printAST(depth + 1);
}

