#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include <variant>
#include "../node.hpp"
#include "../../context/context.hpp"


//base class for constant types
class constant : public node {
public:
	constant(const YYLTYPE& loc) : node(loc){}
	virtual ~constant(){}
	//function to retreive the value of the constant
    virtual std::variant<long , double , char , std::string> getval() const = 0;
};

//integer constant class
class int_constant : public constant {
public:
	int_constant(const YYLTYPE& loc , const int val) :
		constant(loc),
		val_(val) {};

	~int_constant() = default;

	void generateIR() const override;
	void printAST(int depth) const override;

	std::variant<long , double , char , std::string> getval() const override;

private:
	const long val_;
};

//float constant class
class float_constant : public constant {
public:
	float_constant(const YYLTYPE& loc , const double val) :
		constant(loc),
		val_(val) {};

	~float_constant() = default;

	void generateIR() const override;
	void printAST(int depth) const override;

	std::variant<long , double , char , std::string> getval() const override;

private:
	const double val_;
};

//char constant class
class char_constant : public constant {
public:
	char_constant(const YYLTYPE& loc , const char val) :
		constant(loc),
		val_(val) {};

	~char_constant() = default;

	void generateIR() const override;
	void printAST(int depth) const override;

	std::variant<long , double , char , std::string> getval() const override;

private:
	const char val_;
};

class string_literal : public constant {
public:
	string_literal(const YYLTYPE& loc , const std::string val) :
		constant(loc),
		val_(val){}

	~string_literal() = default;

	void generateIR() const override;
	void printAST(int depth) const override;

	std::variant <long , double , char , std::string> getval() const override;

private:
	const std::string val_;
};

class identifier : public node {
public:
	identifier(const YYLTYPE& loc , const std::string id) :
		node(loc),
		identifier_(id) {};

	~identifier(){};

	void generateIR() const override;
	void printAST(int depth) const override;

	void add_type_temp_typedef_check() const override {
		context::insert_custom_type_tmp(identifier_);
	}

private:
	const std::string identifier_;
};

class identifier_list : public nodelist {
public:
	identifier_list(const YYLTYPE& loc , node *first_node) : nodelist(loc , first_node){}

	void printAST(int depth) const override;
};

#endif

