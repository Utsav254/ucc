#pragma once
#include "ast/node.hpp"

class unary : public node {
public:
	unary
	(
		const YYLTYPE& loc , std::unique_ptr<node> cast_expr
	):
		node(loc) , cast_expr_(std::move(cast_expr)) {}

protected:
	std::unique_ptr<node> cast_expr_;
};

class unary_addressof : public unary {
public:
	unary_addressof
	(
		const YYLTYPE& loc , std::unique_ptr<node> cast_expr
	):
		unary(loc , std::move(cast_expr)) {}

	void generateIR() const override;
	void printAST(int depth) const override;
};


class unary_pointer_deref : public unary {
public:
	unary_pointer_deref
	(
		const YYLTYPE& loc , std::unique_ptr<node> cast_expr
  	):
		unary(loc , std::move(cast_expr)) {}

	void generateIR() const override;
	void printAST(int depth) const override;
};


class unary_positive : public unary {
public:
	unary_positive
	(
		const YYLTYPE& loc , std::unique_ptr<node> cast_expr
	):
		unary(loc , std::move(cast_expr)) {}

	void generateIR() const override;
	void printAST(int depth) const override;
};


class unary_negative : public unary {
public:
	unary_negative
	(
		const YYLTYPE& loc , std::unique_ptr<node> cast_expr
  	):
		unary(loc , std::move(cast_expr)) {}

	void generateIR() const override;
	void printAST(int depth) const override;
};


class unary_bitwise_not : public unary {
public:
	unary_bitwise_not
	(
		const YYLTYPE& loc , std::unique_ptr<node> cast_expr
	):
		unary(loc , std::move(cast_expr)) {}

	void generateIR() const override;
	void printAST(int depth) const override;
};


class unary_logical_not : public unary {
public:
	unary_logical_not
	(
		const YYLTYPE& loc , std::unique_ptr<node> cast_expr
	):
		unary(loc , std::move(cast_expr)) {}

	void generateIR() const override;
	void printAST(int depth) const override;
};
