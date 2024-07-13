#ifndef ARRAY_DEFINTION_HPP
#define ARRAY_DEFINTION_HPP

#include "../node.hpp"

class array_definition : public node {
public:
	array_definition(const YYLTYPE&loc , const node *direct_declarator) :
		node(loc),
		direct_declarator_(direct_declarator) {}

	~array_definition() {
		if(direct_declarator_ != nullptr) delete direct_declarator_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

	void add_type_temp_typedef_check() const override {
		direct_declarator_->add_type_temp_typedef_check();
	}

protected:
	const node *direct_declarator_;
};

class array_definition_size : public array_definition {
public:
	array_definition_size(const YYLTYPE& loc , const node *direct_declarator , const node *assignment_expression) :
		array_definition(loc , direct_declarator) , 
		assignment_expression_(assignment_expression) {}

	~array_definition_size() {
		if(assignment_expression_ != nullptr) delete assignment_expression_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

	//will inherit the typedef checker of array defintion

private: 
	const node *assignment_expression_;
};

#endif
