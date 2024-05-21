#ifndef INCR_DECR_OP_HPP
#define INCR_DECR_OP_HPP

#include "../node.hpp"

class postfix_incr : public node {
public:
	postfix_incr(node *postfix_expression) : postfix_expression_(postfix_expression) {}
	~postfix_incr() { 
		if(postfix_expression_ != nullptr) delete postfix_expression_;
	}
	node *clone() const override {
		return new postfix_incr(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *postfix_expression_;
};


class postfix_decr : public node {
public:
	postfix_decr(node *postfix_expression) : postfix_expression_(postfix_expression) {}
	~postfix_decr() { 
		if(postfix_expression_ != nullptr) delete postfix_expression_; 
	}
	node *clone() const override {
		return new postfix_decr(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *postfix_expression_;
};

class unary_incr : public node {
public:
	unary_incr(node *unary_expression) : unary_expression_(unary_expression) {}
	~unary_incr() { 
		if(unary_expression_ != nullptr) delete unary_expression_; 
	}
	node *clone() const override {
		return new unary_incr(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *unary_expression_;
};

class unary_decr : public node {
public:
	unary_decr(node *unary_expression) : unary_expression_(unary_expression) {}
	~unary_decr() { 
		if(unary_expression_ != nullptr) delete unary_expression_;
	}
	node *clone() const override {
		return new unary_decr(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *unary_expression_;
};

#endif
