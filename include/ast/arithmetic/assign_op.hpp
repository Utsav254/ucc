#ifndef ASSIGN_OP_HPP
#define ASSIGN_OP_HPP

#include "../node.hpp"

class assn_op : public node {
public:
	assn_op(const YYLTYPE& loc , const node *unary_expression , const node *assignment_expression):
		node(loc),
		unary_expression_(unary_expression),
		assignment_expression_(assignment_expression) {}

	~assn_op() {
		if(unary_expression_ != nullptr) delete unary_expression_;
		if(assignment_expression_ != nullptr) delete assignment_expression_;
	}

protected: 
	const node *unary_expression_;
	const node *assignment_expression_;
};

class equals_assn : public assn_op {
public:
	equals_assn(const YYLTYPE& loc , const node *unary_expression , const node *assignment_expression) : 
		assn_op(loc , unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class mul_assn : public assn_op {
public:
	mul_assn(const YYLTYPE& loc , const node *unary_expression , const node *assignment_expression) : 
		assn_op(loc , unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class div_assn : public assn_op {
public:
	div_assn(const YYLTYPE& loc , const node *unary_expression , const node *assignment_expression) : 
		assn_op(loc , unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class modu_assn : public assn_op {
public:
	modu_assn(const YYLTYPE& loc , const node *unary_expression , const node *assignment_expression) : 
		assn_op(loc , unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class add_assn : public assn_op {
public:
	add_assn(const YYLTYPE& loc , const node *unary_expression , const node *assignment_expression) : 
		assn_op(loc , unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class sub_assn : public assn_op {
public:
	sub_assn(const YYLTYPE& loc , const node *unary_expression , const node *assignment_expression) : 
		assn_op(loc , unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class left_assn : public assn_op {
public:
	left_assn(const YYLTYPE& loc , const node *unary_expression , const node *assignment_expression) : 
		assn_op(loc , unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class right_assn : public assn_op {
public:
	right_assn(const YYLTYPE& loc , const node *unary_expression , const node *assignment_expression) : 
		assn_op(loc , unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class and_assn : public assn_op {
public:
	and_assn(const YYLTYPE& loc , const node *unary_expression , const node *assignment_expression) : 
		assn_op(loc , unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class xor_assn : public assn_op {
public:
	xor_assn(const YYLTYPE& loc , const node *unary_expression , const node *assignment_expression) : 
		assn_op(loc , unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class or_assn : public assn_op {
public:
	or_assn(const YYLTYPE& loc , const node *unary_expression , const node *assignment_expression) : 
		assn_op(loc , unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class expression_list: public nodelist {
public:
	expression_list(const YYLTYPE& loc , node *first_node) : nodelist(loc , first_node){}
	
	void printAST(int depth) const override;
};

#endif

