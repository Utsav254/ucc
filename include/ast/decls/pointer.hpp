#ifndef POINTER_HPP
#define POINTER_HPP

#include "../node.hpp"
#include "declarator.hpp"


class declarator_pointer : public declarator {
public:
	declarator_pointer(const YYLTYPE&loc , const node *pointer , const node *direct_declarator) :
		declarator(loc , direct_declarator) , pointer_(pointer) {}
	~declarator_pointer() {
		if(pointer_ != nullptr) delete pointer_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

	//should inherit the typedef checker function from the ordinary declarator

private:
	const node *pointer_;
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
	pointer_list(const YYLTYPE& loc , node *first_node) : nodelist(loc , first_node){}

	void printAST(int depth) const override;
};
#endif
