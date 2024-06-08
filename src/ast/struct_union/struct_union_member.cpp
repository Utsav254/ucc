#include "struct_union_member.hpp"
#include <iostream>

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

