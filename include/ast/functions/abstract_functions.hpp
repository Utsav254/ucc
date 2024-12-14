#pragma once
#include "ast/node.hpp"

class unamed_abstract_function_parameters : public node {
public:
	unamed_abstract_function_parameters
	(
		const YYLTYPE& loc,
		std::unique_ptr<node>  param_type_list
	):
		node(loc) , param_type_list_(std::move(param_type_list)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> param_type_list_;
};

class abstract_function : public node {
public:
	abstract_function
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> direct_abstract_decl
	):
		node(loc) , direct_abstract_decl_(std::move(direct_abstract_decl)){}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> direct_abstract_decl_;
};

class abstract_function_parameters : public abstract_function {
public:
	abstract_function_parameters
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> direct_abstract_decl,
		std::unique_ptr<node> param_type_list
	):
		abstract_function(loc , std::move(direct_abstract_decl)),
		param_type_list_(std::move(param_type_list)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node>  param_type_list_;
};


