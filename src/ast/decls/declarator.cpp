#include "declarator.hpp"
#include <iostream>

void declarator::generateIR() const {

}

void declarator::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────declarator" << std::endl;
	if(direct_declarator_ != nullptr) direct_declarator_->printAST(depth + 1);
}

void init_declarator::generateIR() const {

}

void init_declarator::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────init declarator" << std::endl;
	if(declarator_ != nullptr) declarator_->printAST(depth + 1);
}

void init_declarator_ini::generateIR() const {

}

void init_declarator_ini::printAST(int depth) const {
 for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────init declarator initialised" << std::endl;
	if(declarator_ != nullptr) declarator_->printAST(depth + 1);
	if(initialiser_ != nullptr) initialiser_->printAST(depth + 1);
}

