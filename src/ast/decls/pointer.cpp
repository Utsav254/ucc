#include "pointer.hpp"
#include <iostream>

void declarator_pointer::generateIR() const {

}

void declarator_pointer::printAST(int depth) const {
 	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────declarator_pointer" << std::endl;
	if(direct_declarator_ != nullptr) direct_declarator_->printAST(depth + 1);
	if(pointer_ != nullptr) pointer_->printAST(depth + 1);
}

void pointer::generateIR() const {

}

void pointer::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────pointer" << std::endl;
}

void pointer_list::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────pointer_list" << std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}
