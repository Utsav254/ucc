#include "ast/arrays/array_definition.hpp"
#include <iostream>

void array_definition::generateIR () const {

}

void array_definition::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────array_definition" << std::endl;
	if(direct_declarator_ != nullptr) direct_declarator_->printAST(depth + 1);
}

void array_definition_size::generateIR () const {

}

void array_definition_size::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────array_definition_size" << std::endl;
	if(direct_declarator_ != nullptr) direct_declarator_->printAST(depth + 1);
	if(assignment_expression_ != nullptr) assignment_expression_->printAST(depth + 1);
}

void array_definition_type_qual::generateIR () const {

}

void array_definition_type_qual::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────array_definition_typequal" << std::endl;
	if(direct_declarator_ != nullptr) direct_declarator_->printAST(depth + 1);
	if(type_qualifier_list_ != nullptr) type_qualifier_list_->printAST(depth + 1);
}

void array_definition_type_qual_size::generateIR () const {

}

void array_definition_type_qual_size::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
    std::cout << "├────array_definition_type_qual_size" << std::endl;
	if(direct_declarator_ != nullptr) direct_declarator_->printAST(depth + 1);
	if(type_qualifier_list_ != nullptr) type_qualifier_list_->printAST(depth + 1);
	if(assignment_expression_ != nullptr) assignment_expression_->printAST(depth + 1);
}

