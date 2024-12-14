#pragma once
#include "ast/node.hpp"

class enumerator_list : public nodelist {
public:
	enumerator_list
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class enumerator : public node {
public:
	enumerator
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> identifier
	):
		node(loc) , identifier_(std::move(identifier)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> identifier_;
};

class enumerator_const_expr : public enumerator {
public:
	enumerator_const_expr
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> identifier,
		std::unique_ptr<node> const_expr
	):
		enumerator(loc , std::move(identifier)),
		const_expr_(std::move(const_expr)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> const_expr_;
};

