#include "assign_op.hpp"
#include <iostream>

void assn_op::generateIR() const {

}

void assn_op::printAST(int depth) const {

    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
	std::string type;
	switch(a_) {
		case assn::EQUALS : type = "equal";
			break;
		case assn::MUL : type = "mul";
			break;
		case assn::DIV : type = "div";
			break;
		case assn::MOD : type = "mod";
			break;
		case assn::ADD : type = "add";
			break;
		case assn::SUB : type = "sub";
			break;
		case assn::LEFT : type = "left";
			break;
		case assn::RIGHT : type = "right";
			break;
		case assn::AND : type = "and";
			break;
		case assn::XOR : type = "xor";
			break;
		case assn::OR : type = "or";
			break;
		default : type = "unknown";
	}

    std::cout << "├───" << type << " assign" << std::endl;
	if(unary_expression_ != nullptr) unary_expression_->printAST(depth + 1);
	if(assignment_expression_ != nullptr) assignment_expression_->printAST(depth + 1);

}

