#include "misc.hpp"
#include <iostream>

void empty::generateIR() const {

}

void empty::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────Empty" << std::endl;
}

void ellipsis::generateIR() const {

}

void ellipsis::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────ellipsis" << std::endl;
}

void sizeof_node::generateIR() const {

}

void sizeof_node::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────sizeof" << std::endl;
	if(unary_expression_ != nullptr) delete unary_expression_;
}

void sizeof_node_type::generateIR() const {

}

void sizeof_node_type::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────sizeof_type" << std::endl;
	if(type_name_ != nullptr) type_name_->printAST(depth + 1);
}

void translation_unit::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────translation_unit"<< std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}
