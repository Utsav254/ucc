#include "jumps.hpp"
#include <iostream>

void jump_statement_goto::generateIR() const {

}

void jump_statement_goto::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────jump goto" << std::endl;
	if(identifier_ != nullptr) identifier_->printAST(depth + 1);
}

void jump_statement_continue::generateIR() const {

}

void jump_statement_continue::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────jump_continue" << std::endl;
}

void jump_statement_break::generateIR() const {

}

void jump_statement_break::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────jump_break" << std::endl;
}

void jump_statement_ret::generateIR() const {

}

void jump_statement_ret::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────jump_return" << std::endl;
}

void jump_statement_ret_expr::generateIR() const {

}

void jump_statement_ret_expr::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────jump return" << std::endl;
	if(expression_ != nullptr) expression_->printAST(depth + 1);
}

void goto_target::generateIR() const {

}

void goto_target::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────goto target" << std::endl;
	if(identifier_ != nullptr) identifier_->printAST(depth + 1);
	if(statement_ != nullptr) statement_->printAST(depth + 1);

}


