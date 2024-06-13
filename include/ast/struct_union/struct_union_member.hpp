#ifndef STRUCT_UNION_MEMBER_HPP
#define STRUCT_UNION_MEMBER_HPP

#include "../node.hpp"

//declaration members

class specifier_qualifier_list : public nodelist {
public:
	specifier_qualifier_list(node *first_node) : nodelist(first_node){}
	
	void printAST(int depth) const override;
};

//refercing members

class member_op : public node {
public:
	member_op(node *postfix_expression , node *identifier) :
		postfix_expression_(postfix_expression) , identifier_(identifier){}
	~member_op() {
		if(postfix_expression_ != nullptr) delete postfix_expression_;
		if(identifier_ != nullptr) delete identifier_;
	}

protected:
	node *postfix_expression_;
	node *identifier_;
};

class dot_member_op : public member_op {
public:
	dot_member_op(node *postfix_expression , node *identifier) :
		member_op(postfix_expression , identifier){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class ptr_member_op : public member_op {
public:
	ptr_member_op(node *postfix_expression , node *identifier) :
		member_op(postfix_expression , identifier){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};


#endif

