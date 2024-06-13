#include "ast/arithmetic/assign_op.hpp"
#include <iostream>

void equals_assn::generateIR() const {

}

void equals_assn::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────equals_assign"<< std::endl;
	if(unary_expression_ != nullptr) unary_expression_->printAST(depth + 1);
	if(assignment_expression_ != nullptr) assignment_expression_->printAST(depth + 1);
}

void mul_assn::generateIR() const {

}

void mul_assn::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────mul_assign"<< std::endl;
	if(unary_expression_ != nullptr) unary_expression_->printAST(depth + 1);
	if(assignment_expression_ != nullptr) assignment_expression_->printAST(depth + 1);
}

void div_assn::generateIR() const {

}

void div_assn::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────div_assign"<< std::endl;
	if(unary_expression_ != nullptr) unary_expression_->printAST(depth + 1);
	if(assignment_expression_ != nullptr) assignment_expression_->printAST(depth + 1);
}

void modu_assn::generateIR() const {

}

void modu_assn::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────modulo_assign"<< std::endl;
	if(unary_expression_ != nullptr) unary_expression_->printAST(depth + 1);
	if(assignment_expression_ != nullptr) assignment_expression_->printAST(depth + 1);
}

void add_assn::generateIR() const {

}

void add_assn::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────add_assign"<< std::endl;
	if(unary_expression_ != nullptr) unary_expression_->printAST(depth + 1);
	if(assignment_expression_ != nullptr) assignment_expression_->printAST(depth + 1);
}

void sub_assn::generateIR() const {

}

void sub_assn::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────sub_assign"<< std::endl;
	if(unary_expression_ != nullptr) unary_expression_->printAST(depth + 1);
	if(assignment_expression_ != nullptr) assignment_expression_->printAST(depth + 1);
}

void left_assn::generateIR() const {

}

void left_assn::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────left_assign"<< std::endl;
	if(unary_expression_ != nullptr) unary_expression_->printAST(depth + 1);
	if(assignment_expression_ != nullptr) assignment_expression_->printAST(depth + 1);
}

void right_assn::generateIR() const {

}

void right_assn::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────right_assign"<< std::endl;
	if(unary_expression_ != nullptr) unary_expression_->printAST(depth + 1);
	if(assignment_expression_ != nullptr) assignment_expression_->printAST(depth + 1);
}

void and_assn::generateIR() const {

}

void and_assn::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────and_assign"<< std::endl;
	if(unary_expression_ != nullptr) unary_expression_->printAST(depth + 1);
	if(assignment_expression_ != nullptr) assignment_expression_->printAST(depth + 1);
}

void xor_assn::generateIR() const {

}

void xor_assn::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────xor_assign"<< std::endl;
	if(unary_expression_ != nullptr) unary_expression_->printAST(depth + 1);
	if(assignment_expression_ != nullptr) assignment_expression_->printAST(depth + 1);
}

void or_assn::generateIR() const {

}

void or_assn::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────or_assign"<< std::endl;
	if(unary_expression_ != nullptr) unary_expression_->printAST(depth + 1);
	if(assignment_expression_ != nullptr) assignment_expression_->printAST(depth + 1);
}

void expression_list::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────expression_list"<< std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}
