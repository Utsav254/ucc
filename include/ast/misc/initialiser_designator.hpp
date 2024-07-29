#ifndef INITIALISER_DESIGNATOR_HPP
#define INITIALISER_DESIGNATOR_HPP

#include "ast/node.hpp"

class designator_identifier : public node {
public:
	designator_identifier(const YYLTYPE& loc , const node *identifier):
	node(loc) , identifier_(identifier) {}

	~designator_identifier() {
		if(identifier_ != nullptr) delete identifier_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *identifier_;
};

class designator_constant_expr : public node {
public:
	designator_constant_expr(const YYLTYPE& loc , const node *constant_expr) :
		node(loc) , constant_expr_(constant_expr) {}

	~designator_constant_expr() {
		if(constant_expr_ != nullptr) delete constant_expr_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *constant_expr_;
};

class designator_list : public nodelist {
public:
	designator_list(const YYLTYPE&loc , node *first_node) :
		nodelist(loc , first_node){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class designation : public node {
public:
	designation(const YYLTYPE& loc , const nodelist *designator_list , const node *initialiser) :
		node(loc) , designator_list_(designator_list) , initialiser_(initialiser) {}

	~designation() {
		if(designator_list_ != nullptr) delete designator_list_;
		if(initialiser_ != nullptr) delete initialiser_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const nodelist * designator_list_;
	const node * initialiser_;
};

class initialiser_list : public nodelist {
public:
	initialiser_list(const YYLTYPE&loc , node *first_node) :
		nodelist(loc , first_node){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class initialiser : public node {
public:
	initialiser(const YYLTYPE& loc , const nodelist *initialiser_list):
		node(loc) , initialiser_list_(initialiser_list) {}

	~initialiser() {
		if(initialiser_list_ != nullptr) delete initialiser_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const nodelist *initialiser_list_;
};

#endif

