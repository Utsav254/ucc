#ifndef MISC_HPP
#define MISC_HPP

#include "../node.hpp"

class empty : public node {
public:
	empty(const YYLTYPE& loc) : node(loc){}
	~empty(){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class ellipsis : public node {
public:
	ellipsis(const YYLTYPE& loc) : node(loc){}
	~ellipsis(){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class sizeof_node : public node {
public:
	sizeof_node(const YYLTYPE& loc , const node *unary_expression) :
		node(loc),
		unary_expression_(unary_expression){}

	~sizeof_node() {
		if(unary_expression_ != nullptr) delete unary_expression_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *unary_expression_;
};

class sizeof_node_type : public node {
public:
	sizeof_node_type(const YYLTYPE& loc , const node *type_name) :
		node(loc),
		type_name_(type_name){}

	~sizeof_node_type() {
		if(type_name_ != nullptr) delete type_name_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *type_name_;
};

class translation_unit : public nodelist {
public:
	translation_unit(const YYLTYPE& loc , node *first_node) : nodelist(loc , first_node){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class unamed_empty_declaration : public node {
public:
	unamed_empty_declaration(const YYLTYPE& loc) :
		node(loc) {}

	void generateIR() const override;	
	void printAST(int depth) const override;
};

#endif
