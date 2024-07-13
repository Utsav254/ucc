#ifndef SWITCH_CASE_HPP
#define SWITCH_CASE_HPP

#include "../node.hpp"

class switch_node : public node {
public:
	switch_node(const YYLTYPE&loc , const node *expression , const node *statement) :
		node(loc),
		expression_(expression) , statement_(statement){}

	~switch_node() {
		if(expression_ != nullptr) delete expression_;
		if(statement_ != nullptr) delete statement_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *expression_;
	const node *statement_;
};

class case_default_node : public node {
public:
	case_default_node(const YYLTYPE&loc , const node *statement) :
		node(loc),
		statement_(statement){}

	~case_default_node() {
		if(statement_ != nullptr) delete statement_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const node *statement_;
};

class case_node : public case_default_node {
public:
	case_node(const YYLTYPE&loc , const node *statement , const node *constant_expression) : 
		case_default_node(loc , statement) , constant_expression_(constant_expression){}
	~case_node() {
		if(constant_expression_ != nullptr) delete constant_expression_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *constant_expression_;
};


#endif
