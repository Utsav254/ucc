#include <iostream>
#include "identifier.hpp"

void identifier::generateIR() const {
}

void identifier::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────identifier: " << identifier_ << std::endl;
}

