#include "ast/arithmetic/unary.hpp"
#include <iostream>

void unary_addressof::generateIR() const {

}

void unary_addressof::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────unary_address_of" << std::endl;
	if(cast_expr_ != nullptr) cast_expr_->printAST(depth + 1);
}

void unary_pointer_deref::generateIR() const {

}

void unary_pointer_deref::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────unary_pointer_deref" << std::endl;
	if(cast_expr_ != nullptr) cast_expr_->printAST(depth + 1);
}

void unary_positive::generateIR() const {

}

void unary_positive::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────unary_positive" << std::endl;
	if(cast_expr_ != nullptr) cast_expr_->printAST(depth + 1);
}

void unary_negative::generateIR() const {

}

void unary_negative::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────unary_negative" << std::endl;
	if(cast_expr_ != nullptr) cast_expr_->printAST(depth + 1);
}

void unary_bitwise_not::generateIR() const {

}

void unary_bitwise_not::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────unary_bitwise_not" << std::endl;
	if(cast_expr_ != nullptr) cast_expr_->printAST(depth + 1);
}

void unary_logical_not::generateIR() const {

}

void unary_logical_not::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────unary_logical_not: " << std::endl;
	if(cast_expr_ != nullptr) cast_expr_->printAST(depth + 1);
}

