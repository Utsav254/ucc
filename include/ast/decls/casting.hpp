#ifndef CASTING_HPP
#define CASTING_HPP

#include "ast/node.hpp"

class cast_expression : public node {
public:
	cast_expression(const YYLTYPE loc , const node *type_name , const node *cast_expression) :
		node(loc) , type_name_(type_name) , cast_expression_(cast_expression) {}
	~cast_expression() {
		if(type_name_ != nullptr) delete type_name_;
		if(cast_expression_ != nullptr) delete cast_expression_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const node *type_name_;
private:
	const node *cast_expression_;
};

class cast_compound_literal : public cast_expression {
public:
	cast_compound_literal(const YYLTYPE loc , const node *type_name , const nodelist *init_list):
		cast_expression(loc , type_name , nullptr) , 
		init_list_(init_list) {}

	~cast_compound_literal() {
		if(init_list_ != nullptr) delete init_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const nodelist *init_list_;
};

#endif
