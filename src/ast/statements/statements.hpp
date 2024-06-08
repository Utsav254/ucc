#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP

#include "../node.hpp"

enum class statement_type {
	LABELLED,
	COMPOUND,
	EXPRESSION,
	SELECTION,
	ITERATION,
	JUMP,
};

class statement : public node {
public:
	statement(node *statement , statement_type s) : s_(s) , statement_(statement){}
	~statement() {
		if(statement_ != nullptr) delete statement_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private: 
	statement_type s_;
	node *statement_;
};

#endif
