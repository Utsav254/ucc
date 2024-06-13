#include "ast/arrays/array_index.hpp"
#include <iostream>

void array_index::generateIR() const {

}

void array_index::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────array_index: " << std::endl;
	if(postfix_expr_ != nullptr) postfix_expr_->printAST(depth + 1);
	if(expr_ != nullptr) expr_->printAST(depth + 1);
}
