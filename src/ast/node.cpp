#include <iostream>
#include "node.hpp"

void nodelist::generateIR() const {
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		nodes_[i]->generateIR();
	}
}

void nodelist::printAST(int depth) const {

    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
	std::string type;

	switch(lt_) {
		case list_type::DECLARATION : type = "declaration list";
			break;
		case list_type::INIT_DECL : type = "init declaration list";
			break;
		case list_type::TRANSLATION_UNIT : type = "translation unit";
			break;
		case list_type::PARAMETER_TYPE : type = "parameter type list";
			break;
		case list_type::PARAMETER : type = "parameter list";
			break;
		case list_type::ARGUMENT_EXPR : type = "argument expression list";
			break;
		case list_type::ENUMERATOR : type = "enumerator list";
			break;
		case list_type::BLOCK : type = "block list";
			break;
		default: type = "nodelist";
	}

    std::cout << "├────" << type << std::endl;

	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}

void nodelist::pushback(node *next) {
	nodes_.push_back(next);
}
