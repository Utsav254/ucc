#include "statements.hpp"
#include <iostream>

void statement::generateIR() const {
	
}

void statement::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
	std::string type;

	switch(s_) {
		case statement_type::LABELLED : type = "labelled";
			break;
		case statement_type::COMPOUND : type = "compound";
			break;
		case statement_type::EXPRESSION : type = "expression";
			break;
		case statement_type::SELECTION : type = "selection";
			break;
		case statement_type::ITERATION : type = "iteration";
			break;
		case statement_type::JUMP : type = "jump";
			break;
		default : type = "unknown";
	}
    std::cout << "├────" << type << " statement" << std::endl;
	if(statement_ != nullptr) statement_->printAST(depth + 1);

}
