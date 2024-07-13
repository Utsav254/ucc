#ifndef WHILE_HPP
#define WHILE_HPP

#include "../node.hpp"

class while_node : public node {
public:
	while_node(const YYLTYPE&loc , const node *expression , const node *statement) :
		node(loc),
		expression_(expression) , statement_(statement){}

	~while_node() {
		if(expression_ != nullptr) delete expression_;
		if(statement_ != nullptr) delete statement_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const node *expression_;
	const node *statement_;
};

class do_while_node : public while_node {
public:
	do_while_node(const YYLTYPE&loc , const node *statement , const node *expression) :
		while_node(loc , expression , statement){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

#endif


