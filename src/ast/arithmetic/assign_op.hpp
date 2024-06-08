#ifndef ASSIGN_OP_HPP
#define ASSIGN_OP_HPP

#include "../node.hpp"

enum class assn {
	EQUALS,
	MUL, DIV, MOD,
	ADD, SUB,
	LEFT, RIGHT,
	AND, XOR, OR,
};

class assn_op : public node {
public:
	assn_op(node *unary_expression , node *assignment_expression , assn a):
		unary_expression_(unary_expression),
		assignment_expression_(assignment_expression),
		a_(a){}
	~assn_op() {
		if(unary_expression_ != nullptr) delete unary_expression_;
		if(assignment_expression_ != nullptr) delete assignment_expression_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private: 
	node *unary_expression_;
	node *assignment_expression_;
	assn a_;
};

#endif
