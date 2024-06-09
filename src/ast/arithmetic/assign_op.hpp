#ifndef ASSIGN_OP_HPP
#define ASSIGN_OP_HPP

#include "../node.hpp"

class assn_op : public node {
public:
	assn_op(node *unary_expression , node *assignment_expression):
		unary_expression_(unary_expression),
		assignment_expression_(assignment_expression) {}

	~assn_op() {
		if(unary_expression_ != nullptr) delete unary_expression_;
		if(assignment_expression_ != nullptr) delete assignment_expression_;
	}

protected: 
	node *unary_expression_;
	node *assignment_expression_;
};

class equals_assn : public assn_op {
public:
	equals_assn(node *unary_expression , node *assignment_expression) : 
		assn_op(unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class mul_assn : public assn_op {
public:
	mul_assn(node *unary_expression , node *assignment_expression) : 
		assn_op(unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class div_assn : public assn_op {
public:
	div_assn(node *unary_expression , node *assignment_expression) : 
		assn_op(unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class modu_assn : public assn_op {
public:
	modu_assn(node *unary_expression , node *assignment_expression) : 
		assn_op(unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class add_assn : public assn_op {
public:
	add_assn(node *unary_expression , node *assignment_expression) : 
		assn_op(unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class sub_assn : public assn_op {
public:
	sub_assn(node *unary_expression , node *assignment_expression) : 
		assn_op(unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class left_assn : public assn_op {
public:
	left_assn(node *unary_expression , node *assignment_expression) : 
		assn_op(unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class right_assn : public assn_op {
public:
	right_assn(node *unary_expression , node *assignment_expression) : 
		assn_op(unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class and_assn : public assn_op {
public:
	and_assn(node *unary_expression , node *assignment_expression) : 
		assn_op(unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class xor_assn : public assn_op {
public:
	xor_assn(node *unary_expression , node *assignment_expression) : 
		assn_op(unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class or_assn : public assn_op {
public:
	or_assn(node *unary_expression , node *assignment_expression) : 
		assn_op(unary_expression , assignment_expression){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class expression_list: public nodelist {
public:
	expression_list(node *first_node) : nodelist(first_node){}
	
	void printAST(int depth) const override;
};

#endif

