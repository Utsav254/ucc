#ifndef WHILE_HPP
#define WHILE_HPP

#include "../node.hpp"

class while_node : public node {
public:
	while_node(node *expression , node *statement) :
		expression_(expression) , statement_(statement){}
	~while_node() {
		if(expression_ != nullptr) delete expression_;
		if(statement_ != nullptr) delete statement_;
	}
	node *clone() const override {
		return new while_node(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *expression_;
	node *statement_;
};

class do_while_node : public node {
public:
	do_while_node(node *statement , node *expression) :
		statement_(statement) , expression_(expression){}
	~do_while_node() {
		if(expression_ != nullptr) delete expression_;
		if(statement_ != nullptr) delete statement_;
	}
	node *clone() const override {
		return new do_while_node(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *statement_;
	node *expression_;
};

#endif


