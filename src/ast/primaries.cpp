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

std::variant<long , double , char> int_constant::getval() const {
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

std::variant<long , double , char> float_constant::getval() const {
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

std::variant<long , double , char> char_constant::getval() const {
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

