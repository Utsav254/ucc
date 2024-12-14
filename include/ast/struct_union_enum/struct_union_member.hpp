#pragma once
#include "../node.hpp"

class specifier_qualifier_list : public nodelist {
public:
	specifier_qualifier_list
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}
	
	void printAST(int depth) const override;
};

//virtual class for referencing
class member_op : public node {
public:
	member_op
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> postfix_expression,
		std::unique_ptr<node> identifier
	):
		node(loc),
		postfix_expression_(std::move(postfix_expression)) , identifier_(std::move(identifier)){}

protected:
	std::unique_ptr<node> postfix_expression_;
	std::unique_ptr<node> identifier_;
};

class dot_member_op : public member_op {
public:
	dot_member_op
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> postfix_expression,
		std::unique_ptr<node> identifier
	):
		member_op(loc , std::move(postfix_expression) , std::move(identifier)){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

class ptr_member_op : public member_op {
public:
	ptr_member_op
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> postfix_expression,
		std::unique_ptr<node> identifier
	):
		member_op(loc, std::move(postfix_expression), std::move(identifier)){}
	
	void generateIR() const override;
	void printAST(int depth) const override;
};

