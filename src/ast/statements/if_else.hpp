#ifndef IFS_HPP
#define IFS_HPP

#include "../node.hpp"

class if_node : public node {
public:
	if_node(node *expression , node *if_body) : 
		expression_(expression) , if_body_(if_body){}
	~if_node() {
		if(expression_ != nullptr) delete expression_;
		if(if_body_ != nullptr) delete if_body_;
	}
	node *clone() const override {
		return new if_node(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	node *expression_;
	node *if_body_;
};

class if_else_node : public if_node {
public:
	if_else_node(node *expression , node *if_body , node *else_body) :
		if_node(expression , if_body) , else_body_(else_body){}
	~if_else_node() {
		if(else_body_ != nullptr) delete else_body_;
	}
	node *clone() const override {
		return new if_else_node(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *else_body_;
};

#endif

