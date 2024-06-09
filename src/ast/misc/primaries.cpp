#include <iostream>
#include "primaries.hpp"

void int_constant::generateIR() const {
}

void int_constant::printAST(int depth) const {

    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────integer: " << val_ << std::endl;
}

std::variant<long , double , char , std::string> int_constant::getval() const {
	return val_;
}


void float_constant::generateIR() const {
}

void float_constant::printAST(int depth) const {

    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────float: " << val_ << std::endl;
}

std::variant<long , double , char , std::string> float_constant::getval() const {
	return val_;
}


void char_constant::generateIR() const {
}

void char_constant::printAST(int depth) const {

    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────char(int): " << (int)val_ << std::endl;
}

std::variant<long , double , char , std::string> char_constant::getval() const {
	return val_;
}

void string_literal::generateIR() const {

}

void string_literal::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────string_literal: " << val_ << std::endl;
}

std::variant <long , double , char , std::string>string_literal::getval() const {
	return val_;
}


void identifier::generateIR() const {
}

void identifier::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────identifier: " << identifier_ << std::endl;
}

void identifier_list::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────identifier_list"<< std::endl;
	for(int i = 0 ; i < (int)nodes_.size() ; i++) {
		if(nodes_[i] != nullptr) nodes_[i]->printAST(depth + 1);
	}
}


