#include "ast/misc/initialiser_designator.hpp"
#include <iostream>

void designator_identifier::generateIR() const {

}

void designator_identifier::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────designator_identifier"<< std::endl;
	if(identifier_ != nullptr) identifier_->printAST(depth + 1);
}


void designator_constant_expr::generateIR() const {

}

void designator_constant_expr::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────designator_constant_expr" << std::endl;
	if(constant_expr_ != nullptr) constant_expr_->printAST(depth + 1);
}


void designator_list::generateIR() const {

}

void designator_list::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────designator_list " << std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}


void designation::generateIR() const {

}

void designation::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────designation" << std::endl;
	if(designator_list_ != nullptr) designator_list_->printAST(depth + 1);
	if(initialiser_ != nullptr) initialiser_->printAST(depth + 1);
}


void initialiser_list::generateIR() const {

}

void initialiser_list::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────initialiser_list" << std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}

void initialiser::generateIR() const {

}

void initialiser::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────initialiser" << std::endl;
	if(initialiser_list_ != nullptr) initialiser_list_->printAST(depth + 1);
}

