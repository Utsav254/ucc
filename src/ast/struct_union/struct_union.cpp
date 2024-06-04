#include "struct_union.hpp"
#include <iostream>

void struct_union::generateIR() const {

}

void struct_union::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}

	std::string type;
	switch(su_) {
		case structorunion::STRUCT: type = "struct";
			break;
		case structorunion::UNION: type = "union";
			break;
		default: type = "unknown";
	}
	std::cout << "├────struct_union: " << type << std::endl;
}

void struct_union_spec_id::generateIR() const {

}

void struct_union_spec_id::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────struct_union_spec_id" << std::endl;
	if(struct_union_ != nullptr) struct_union_->printAST(depth + 1);
	if(identifier_ != nullptr) identifier_->printAST(depth + 1);
}

void struct_union_spec_id_decl::generateIR() const {

}

void struct_union_spec_id_decl::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────struct_union_spec_id_decl" << std::endl;
	if(struct_union_ != nullptr) struct_union_->printAST(depth + 1);
	if(identifier_ != nullptr) identifier_->printAST(depth + 1);
	if(struct_decl_list_ != nullptr) struct_decl_list_->printAST(depth + 1);
}

void struct_union_spec_decl::generateIR() const {

}

void struct_union_spec_decl::printAST(int depth) const {
	for(int i = 0 ; i < depth-1 ; i++){
		std::cout << "│\t";
	}
	std::cout << "├────struct_union_spec_unnamed_decl" << std::endl;
	if(struct_union_ != nullptr) struct_union_->printAST(depth + 1);
	if(struct_decl_list_ != nullptr) struct_decl_list_->printAST(depth + 1);
}


