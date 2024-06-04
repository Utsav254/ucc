#ifndef MISC_HPP
#define MISC_HPP

#include "node.hpp"

class empty : public node {
public:
	empty(){}
	~empty(){}
	node* clone() const override {
		return new empty(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class ellipsis : public node {
public:
	ellipsis(){}
	~ellipsis(){}
	node *clone() const override {
		return new ellipsis(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;
};

#endif
