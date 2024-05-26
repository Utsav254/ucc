#include "jumps.hpp"
#include <iostream>

void jump_statement::generateIR() const {

}

void jump_statement::printAST(int depth) const {

    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
	std::string type;

	switch(j_) {
		case jump_type::GOTO : type = "goto";
			break;
		case jump_type::CONTINUE : type = "continue";
			break;
		case jump_type::BREAK : type = "break";
			break;
		case jump_type::RETURN : type = "return";
			break;
		default : type = "unknown";
	}
    std::cout << "├────jump " << type << std::endl;

}

void jump_statement_goto::generateIR() const {

}

void jump_statement_goto::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────jump goto" << std::endl;
	if(identifier_ != nullptr) identifier_->printAST(depth + 1);
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


