#ifndef MISC_HPP
#define MISC_HPP

#include "../node.hpp"

class empty : public node {
public:
	empty(){}
	~empty(){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class ellipsis : public node {
public:
	ellipsis(){}
	~ellipsis(){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class sizeof_node : public node {
public:
	sizeof_node(node *unary_expression) : unary_expression_(unary_expression){}
	~sizeof_node() {
		if(unary_expression_ != nullptr) delete unary_expression_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *unary_expression_;
};

class sizeof_node_type : public node {
public:
	sizeof_node_type(node *type_name) : type_name_(type_name){}
	~sizeof_node_type() {
		if(type_name_ != nullptr) delete type_name_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *type_name_;
};

class translation_unit : public nodelist {
public:
	translation_unit(node *first_node) : nodelist(first_node){}

	void printAST(int depth) const override;
};


#endif
