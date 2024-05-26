#ifndef SWITCH_CASE_HPP
#define SWITCH_CASE_HPP

#include "../node.hpp"

class switch_node : public node {
public:
	switch_node(node *expression , node *statement) : 
		expression_(expression) , statement_(statement){}

	~switch_node() {
		if(expression_ != nullptr) delete expression_;
		if(statement_ != nullptr) delete statement_;
	}
	node *clone() const override {
		return new switch_node(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *expression_;
	node *statement_;
};

class case_default_node : public node {
public:
	case_default_node(node *statement) : statement_(statement){}
	~case_default_node() {
		if(statement_ != nullptr) delete statement_;
	}
	node *clone() const override {
		return new case_default_node(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	node *statement_;
};

class case_node : public case_default_node {
public:
	case_node(node *statement , node *constant_expression) : 
		case_default_node(statement) , constant_expression_(constant_expression){}
	~case_node() {
		if(constant_expression_ != nullptr) delete constant_expression_;
	}
	node *clone() const override {
		return new case_node(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *constant_expression_;
};


#endif
