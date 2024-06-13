#include "ast/functions/function_definition.hpp"
#include <iostream>

void function_definition::generateIR() const {

}

void function_definition::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────function defintion" << std::endl;
	if(declaration_specifiers_ != nullptr) declaration_specifiers_->printAST(depth + 1);
	if(declarator_ != nullptr) declarator_->printAST(depth + 1);
	if(compound_statement_ != nullptr) compound_statement_->printAST(depth + 1);
}

void function_definition_decl_list::generateIR() const {

}

void function_definition_decl_list::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────function defintion with decl list " << std::endl;
	if(declaration_specifiers_ != nullptr) declaration_specifiers_->printAST(depth + 1);
	if(declarator_ != nullptr) declarator_->printAST(depth + 1);
	if(declaration_list_ != nullptr) declaration_list_->printAST(depth + 1);
	if(compound_statement_ != nullptr) compound_statement_->printAST(depth + 1);
}

