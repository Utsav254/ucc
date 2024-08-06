#include "ast/functions/function_pointer.hpp"
#include <iostream>

void function_ptr::generateIR() const {

}

void function_ptr::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────function_pointer" << std::endl;
	if(declarator_ != nullptr) declarator_->printAST(depth + 1);
}
