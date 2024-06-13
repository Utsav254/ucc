#ifndef ARRAY_INDEX_HPP
#define ARRAY_INDEX_HPP

#include "../node.hpp"

class array_index : public node {
public:
	array_index(node *postfix_expr , node *expr) : postfix_expr_(postfix_expr) , expr_(expr){}
	~array_index() {
		if(postfix_expr_ != nullptr) delete postfix_expr_;
		if(expr_ != nullptr) delete expr_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *postfix_expr_;
	node *expr_;
};

#endif
