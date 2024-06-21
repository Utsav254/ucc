#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include <variant>
#include "../node.hpp"
#include "../../context.hpp"


//base class for constant types
class constant : public node {
public:
	virtual ~constant(){}
	//function to retreive the value of the constant
    virtual std::variant<long , double , char , std::string> getval() const = 0;
};

//integer constant class
class int_constant : public constant {
public:
	int_constant(int val) : val_(val) {};
	~int_constant() = default;

	void generateIR() const override;
	void printAST(int depth) const override;

	std::variant<long , double , char , std::string> getval() const override;

private:
	long val_;
};

//float constant class
class float_constant : public constant {
public:
	float_constant(int val) : val_(val) {};
	~float_constant() = default;

	void generateIR() const override;
	void printAST(int depth) const override;

	std::variant<long , double , char , std::string> getval() const override;

private:
	double val_;
};

//char constant class
class char_constant : public constant {
public:
	char_constant(int val) : val_(val) {};
	~char_constant() = default;

	void generateIR() const override;
	void printAST(int depth) const override;

	std::variant<long , double , char , std::string> getval() const override;

private:
	char val_;
};

class string_literal : public constant {
public:
	string_literal(std::string val) : val_(val){}
	~string_literal() = default;

	void generateIR() const override;
	void printAST(int depth) const override;

	std::variant <long , double , char , std::string> getval() const override;

private:
	std::string val_;
};

class identifier : public node {
public:
	identifier(std::string id) : identifier_(id) {};
	~identifier(){};

	void generateIR() const override;
	void printAST(int depth) const override;

	void add_type_temp_typedef_check() const override {
		context::insert_custom_type_tmp(identifier_);
	}

private:
	std::string identifier_;
};

class identifier_list : public nodelist {
public:
	identifier_list(node *first_node) : nodelist(first_node){}

	void printAST(int depth) const override;
};

#endif

