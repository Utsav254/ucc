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
		case type_specifiers::VOID : 
			type = "void";
			break;
		case type_specifiers::CHAR : 
			type = "char";
			break;
		case type_specifiers::INT : 
			type = "int";
			break;
		case type_specifiers::FLOAT : 
			type = "float";
			break;
		case type_specifiers::DOUBLE : 
			type = "double";
			break;
		case type_specifiers::SHORT : 
			type = "short";
			break;
		case type_specifiers::LONG : 
			type = "long";
			break;
		case type_specifiers::SIGNED : 
			type = "signed";
			break;
		case type_specifiers::UNSIGNED : 
			type = "unsigned";
			break;
		case type_specifiers::STRUCT_OR_UNION : 
			type = "struct/union";
			break;
		case type_specifiers::ENUM : 
			type = "enum";
			break;
		case type_specifiers::TYPEDEF_NAME : 
			type = "typedef_name";
			break;
		default: type = "unknown";
	}
    std::cout << "├────type_specifier: " << type << std::endl;
}

void type_qualifier::generateIR() const {

}

void type_qualifier::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::string type;

	switch(q_) {
		case type_qualifiers::CONST : 
			type = "const";
			break;
		case type_qualifiers::RESTRICT : 
			type = "restrict";
			break;
		case type_qualifiers::VOLATILE : 
			type = "volatile";
			break;
		default: type = "unknown";

	}

	std::cout << "├────type_qualifier: " << type << std::endl;
}

void storage_class_specifier::generateIR() const {

}

void storage_class_specifier::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::string type;

	switch(s_) {
		case storage_specifiers::TYPEDEF : 
			type = "typedef";
			break;
		case storage_specifiers::EXTERN : 
			type = "extern";
			break;
		case storage_specifiers::STATIC : 
			type = "static";
			break;
		case storage_specifiers::AUTO : 
			type = "auto";
			break;
		case storage_specifiers::REGISTER :
			type = "register";
			break;
		default: type = "unknown";

	}
	std::cout << "├────storage_specifier: " << type << std::endl;
}

void function_specifier::generateIR() const {

}

void function_specifier::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::string type;
	switch(f_) {
		case function_specifiers::INLINE :
			type = "inline";
			break;
		default : type = "unknown";
	}
	std::cout << "├────function_specifier: " << type << std::endl;
}



