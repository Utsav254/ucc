#ifndef ARRAY_DEFINTION_HPP
#define ARRAY_DEFINTION_HPP

#include "../node.hpp"

class array_definition : public node {
public:
	array_definition(node *direct_declarator) : direct_declarator_(direct_declarator) {}
	~array_definition() {
		if(direct_declarator_ != nullptr) delete direct_declarator_;
	}
	node *clone() const override {
		return new array_definition(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	node *direct_declarator_;
};

class array_definition_size : public array_definition {
public:
	array_definition_size(node *direct_declarator , node *assignment_expression) : 
		array_definition(direct_declarator) , 
		assignment_expression_(assignment_expression) {}

	~array_definition_size() {
		if(assignment_expression_ != nullptr) delete assignment_expression_;
	}
	node *clone() const override {
		return new array_definition(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private: 
	node *assignment_expression_;
};

#endif
