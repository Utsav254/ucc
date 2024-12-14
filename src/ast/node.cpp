#include <iostream>
#include "ast/node.hpp"

void nodelist::generateIR() const {
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		nodes_[i]->generateIR();
	}
}

void nodelist::printAST(int depth) const {

    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────nodelist" << std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}

void nodelist::pushback(std::unique_ptr<node> next) {
	nodes_.push_back(std::move(next));
}
