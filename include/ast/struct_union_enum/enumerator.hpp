#ifndef ENUMERATOR_HPP
#define ENUMERATOR_HPP

#include "ast/node.hpp"

class enumerator_list : public nodelist {
public:
	enumerator_list(const YYLTYPE& loc , node *first_node) : nodelist(loc , first_node){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class enumerator : public node {
public:
	enumerator(const YYLTYPE& loc , const node *identifier) :
		node(loc) , identifier_(identifier) {}
	~enumerator() {
		if(identifier_ != nullptr) delete identifier_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const node *identifier_;
};

class enumerator_const_expr : public enumerator {
public:
	enumerator_const_expr(const YYLTYPE& loc , const node *identifier , const node *const_expr) :
		enumerator(loc , identifier) , const_expr_(const_expr) {}

	~enumerator_const_expr() {
		if(const_expr_ != nullptr) delete const_expr_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *const_expr_;
};

#endif
