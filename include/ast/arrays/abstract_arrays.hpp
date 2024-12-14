#pragma once
#include "ast/node.hpp"

class unamed_empty_array : public node {
public:
	unamed_empty_array
	(
		const YYLTYPE& loc
	):
		node(loc) {}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class unamed_empty_array_size : public unamed_empty_array {
public:
	unamed_empty_array_size
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> assignment_expr
	):
		unamed_empty_array(loc)  , assignment_expr_(std::move(assignment_expr)){}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> assignment_expr_;
};

class array_decl_abstract : public unamed_empty_array {
public:
	array_decl_abstract
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> direct_abstract_decl
	):
		unamed_empty_array(loc) , direct_abstract_decl_(std::move(direct_abstract_decl)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> direct_abstract_decl_;
};

class array_decl_abstract_size : public unamed_empty_array_size {
public:
	array_decl_abstract_size
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> direct_abstract_decl,
		std::unique_ptr<node> assignment_expr
	):
		unamed_empty_array_size(loc , std::move(assignment_expr)), 
		direct_abstract_decl_(std::move(direct_abstract_decl)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> direct_abstract_decl_;
};
