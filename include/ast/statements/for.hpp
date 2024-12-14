#pragma once
#include "../node.hpp"

class for_node : public node {
public:
	for_node
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> declaration,
		std::unique_ptr<node> condition_expr,
		std::unique_ptr<node> statement
	):
		node(loc),
		declaration_(std::move(declaration)),
		condition_expr_(std::move(condition_expr)),
		statement_(std::move(statement)){}
	
	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> declaration_;
	std::unique_ptr<node> condition_expr_;
	std::unique_ptr<node> statement_;
};

class for_node_mod : public for_node {
public:
	for_node_mod
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> declaration,
		std::unique_ptr<node> condition_expr,
		std::unique_ptr<node> statement,
		std::unique_ptr<node> modifying_expr
	):
		for_node(loc, std::move(declaration), std::move(condition_expr), std::move(statement)),
		modifying_expr_(std::move(modifying_expr)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> modifying_expr_;
};


class for_node_ext : public node {
public:
	for_node_ext
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> initial_expr,
		std::unique_ptr<node> condition_expr,
		std::unique_ptr<node> statement
	):
		node(loc),
		initial_expr_(std::move(initial_expr)),
		condition_expr_(std::move(condition_expr)),
		statement_(std::move(statement)){}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> initial_expr_;
	std::unique_ptr<node> condition_expr_;
	std::unique_ptr<node> statement_;
};

class for_node_ext_mod : public for_node_ext {
public:
	for_node_ext_mod
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> initial_expr,
		std::unique_ptr<node> condition_expr,
		std::unique_ptr<node> statement,
		std::unique_ptr<node> modifying_expr
	):
		for_node_ext(loc , std::move(initial_expr), std::move(condition_expr), std::move(statement)),
		modifying_expr_(std::move(modifying_expr)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> modifying_expr_;
};

