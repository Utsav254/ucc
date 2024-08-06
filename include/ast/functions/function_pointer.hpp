#ifndef FUNCTION_POINTER_HPP
#define FUNCTION_POINTER_HPP

#include "ast/node.hpp"

class function_ptr : public node {
public:
	function_ptr(const YYLTYPE& loc , const node *declarator) : 
		node(loc) , declarator_(declarator) {}

	~function_ptr() {
		if(declarator_ != nullptr) delete declarator_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *declarator_;
};

#endif
