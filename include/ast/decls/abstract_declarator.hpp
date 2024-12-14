#pragma once
#include "ast/node.hpp"

class abstract_declarator : public node {
public:
	abstract_declarator
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> abstract_direct_decl
	): 
		node(loc) , abstract_direct_decl_(std::move(abstract_direct_decl)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> abstract_direct_decl_;
};


class abstract_declarator_pointer : public abstract_declarator {
public:
	abstract_declarator_pointer
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> pointer,
		std::unique_ptr<node> abstract_direct_decl
	): 
		abstract_declarator(loc , std::move(abstract_direct_decl)),
		pointer_(std::move(pointer)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> pointer_;
};

