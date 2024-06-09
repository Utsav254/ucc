#include "struct_union_member.hpp"
#include <iostream>

void specifier_qualifier_list::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────spec_qual_list" << std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}

void dot_member_op::generateIR() const {

}

void dot_member_op::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────dot_member: " << std::endl;
	if(postfix_expression_ != nullptr) postfix_expression_->printAST(depth + 1);
	if(identifier_ != nullptr) identifier_->printAST(depth + 1);
}

void ptr_member_op::generateIR() const {

}

void ptr_member_op::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────ptr_member: " << std::endl;
	if(postfix_expression_ != nullptr) postfix_expression_->printAST(depth + 1);
	if(identifier_ != nullptr) identifier_->printAST(depth + 1);
}

