#ifndef INCR_DECR_OP_HPP
#define INCR_DECR_OP_HPP

#include "../node.hpp"

class postfix_incr : public node {
public:
	postfix_incr(const YYLTYPE& loc , const node *postfix_expression):
		node(loc),
		postfix_expression_(postfix_expression) {}

	~postfix_incr() { 
		if(postfix_expression_ != nullptr) delete postfix_expression_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *postfix_expression_;
};


class postfix_decr : public node {
public:
	postfix_decr(const YYLTYPE& loc , const node *postfix_expression) :
		node(loc),
		postfix_expression_(postfix_expression) {}

	~postfix_decr() { 
		if(postfix_expression_ != nullptr) delete postfix_expression_; 
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *postfix_expression_;
};

class unary_incr : public node {
public:
	unary_incr(const YYLTYPE& loc , const node *unary_expression) :
		node(loc),
		unary_expression_(unary_expression) {}

	~unary_incr() { 
		if(unary_expression_ != nullptr) delete unary_expression_; 
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *unary_expression_;
};

class unary_decr : public node {
public:
	unary_decr(const YYLTYPE& loc , const node *unary_expression) :
		node(loc),
		unary_expression_(unary_expression) {}

	~unary_decr() { 
		if(unary_expression_ != nullptr) delete unary_expression_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *unary_expression_;
};

#endif
