#include "specifier_qualifiers.hpp"
#include <iostream>

void type_specifier::generateIR() const {

}

void type_specifier::printAST(int depth) const {
    for(int i = 0 ; i < depth-1 ; i++){
        std::cout << "│\t";
    }
	std::string type;
	
	switch(t_) {
		case types::VOID : 
			type = "void";
			break;
		case types::CHAR : 
			type = "char";
			break;
		case types::INT : 
			type = "int";
			break;
		case types::FLOAT : 
			type = "float";
			break;
		case types::DOUBLE : 
			type = "double";
			break;
		case types::SHORT : 
			type = "short";
			break;
		case types::LONG : 
			type = "long";
			break;
		case types::SIGNED : 
			type = "signed";
			break;
		case types::UNSIGNED : 
			type = "unsigned";
			break;
		case types::STRUCT_OR_UNION : 
			type = "struct/union";
			break;
		case types::ENUM : 
			type = "enum";
			break;
		case types::TYPEDEF_NAME : 
			type = "typedef_name";
			break;
		default: type = "unknown";
	}
    std::cout << "├────type_specifier: " << type << std::endl;
}
