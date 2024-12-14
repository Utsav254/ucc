#pragma once
#include "../node.hpp"
#include "declarator.hpp"


class declarator_pointer : public declarator {
public:
	declarator_pointer
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> pointer,
		std::unique_ptr<node> direct_declarator
	):
		declarator(loc , std::move(direct_declarator)),
		pointer_(std::move(pointer)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

	//should inherit the typedef checker function from the ordinary declarator

private:
	std::unique_ptr<node> pointer_;
};

class pointer : public node {
public:
	pointer(const YYLTYPE& loc) : node(loc){}
	~pointer(){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class pointer_list : public nodelist {
public:
	pointer_list
	(
		const YYLTYPE& loc , std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}

	void printAST(int depth) const override;
};
