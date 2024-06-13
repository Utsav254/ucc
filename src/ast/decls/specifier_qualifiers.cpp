#include "ast/decls/specifier_qualifiers.hpp"
#include <iostream>

void type_specifier::generateIR() const {

}

void type_specifier::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────type_specifier: " << type_spec_ << std::endl;
}

void type_qualifier::generateIR() const {

}

void type_qualifier::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────type_qualifier: " << type_qual_ << std::endl;
}

void storage_class_specifier::generateIR() const {

}

void storage_class_specifier::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────storage_specifier: " << storage_class_spec_ << std::endl;
}

void function_specifier::generateIR() const {

}

void function_specifier::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────function_specifier: " << function_spec_ << std::endl;
}


void declaration_specifiers::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────declaration_specifiers"<< std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}

void type_qualifier_list::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────type_qualifier_list"<< std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}

