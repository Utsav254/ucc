#pragma once
#include "../node.hpp"
#include "context/context_type_tmp.hpp"

//base class for constant types
class constant : public node {
public:
	constant(const YYLTYPE& loc) : node(loc){}
	virtual ~constant(){}
};

//integer constant class
class int_constant : public constant {
public:
	int_constant(const YYLTYPE& loc , const int val) :
		constant(loc),
		val_(val) {};


	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const long val_;
};

//float constant class
class float_constant : public constant {
public:
	float_constant(const YYLTYPE& loc , const double val) :
		constant(loc),
		val_(val) {};

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const double val_;
};

//char constant class
class char_constant : public constant {
public:
	char_constant(const YYLTYPE& loc , const char val) :
		constant(loc),
		val_(val) {};

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const char val_;
};

class string_literal : public constant {
public:
	string_literal(const YYLTYPE& loc , std::unique_ptr<std::string> val) :
		constant(loc),
		val_(std::move(val)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<std::string> val_;
};

class identifier : public node {
public:
	identifier(const YYLTYPE& loc , std::unique_ptr<std::string> id) :
		node(loc),
		identifier_(std::move(id)) {};

	void generateIR() const override;
	void printAST(int depth) const override;

	void add_type_temp_typedef_check() const override {
		context::insert_custom_type_tmp(*identifier_);
	}

private:
	std::unique_ptr<std::string> identifier_;
};

class identifier_list : public nodelist {
public:
	identifier_list
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}

	void printAST(int depth) const override;
};

