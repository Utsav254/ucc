#pragma once
#include "ast/node.hpp"

class cast_expression : public node {
public:
	cast_expression
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> type_name,
		std::unique_ptr<node> cast_expression
	):
		node(loc) , type_name_(std::move(type_name)),
		cast_expression_(std::move(cast_expression)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> type_name_;
private:
	std::unique_ptr<node> cast_expression_;
};

class cast_compound_literal : public cast_expression {
public:
	cast_compound_literal
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> type_name,
		std::unique_ptr<node> init_list
	):
		cast_expression(loc , std::move(type_name) , nullptr) , 
		init_list_(std::move(init_list)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> init_list_;
};

