#include "declaration_specifier.hpp"
#include <iostream>

void declaration_specifier::generateIR() const {

}

void declaration_specifier::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────declaration specifier" << std::endl;
	if(main_specifier_ != nullptr) main_specifier_->printAST(depth + 1);	
}

void declaration_specifier_double::generateIR() const {

}

void declaration_specifier_double::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────declaration specifier (double)" << std::endl;
	if(main_specifier_ != nullptr) main_specifier_->printAST(depth + 1);
	if(modifying_specifier_ != nullptr) modifying_specifier_->printAST(depth + 1);
}
