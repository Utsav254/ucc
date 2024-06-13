#include "ast/arithmetic/incr_decr_op.hpp"
#include <iostream>

void postfix_incr::generateIR() const {

}

void postfix_incr::printAST(int depth) const {

    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────postfix incr: " << std::endl;
	if(postfix_expression_ != nullptr) postfix_expression_->printAST(depth + 1);
}

void postfix_decr::generateIR() const {

}

void postfix_decr::printAST(int depth) const {

    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────postfix decr: " << std::endl;
	if(postfix_expression_ != nullptr) postfix_expression_->printAST(depth + 1);
}

void unary_incr::generateIR() const {

}

void unary_incr::printAST(int depth) const {

    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────unary incr: " << std::endl;
	if(unary_expression_ != nullptr) unary_expression_->printAST(depth + 1);
}

void unary_decr::generateIR() const {

}

void unary_decr::printAST(int depth) const {

    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────unary decr: " << std::endl;
	if(unary_expression_ != nullptr) unary_expression_->printAST(depth + 1);
}

