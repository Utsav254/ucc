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
