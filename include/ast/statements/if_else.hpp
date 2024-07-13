#ifndef IFS_HPP
#define IFS_HPP

#include "../node.hpp"

class if_node : public node {
public:
	if_node(const YYLTYPE&loc , const node *expression , const node *if_body) :
		node(loc),
		expression_(expression) , if_body_(if_body){}

	~if_node() {
		if(expression_ != nullptr) delete expression_;
		if(if_body_ != nullptr) delete if_body_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const node *expression_;
	const node *if_body_;
};

class if_else_node : public if_node {
public:
	if_else_node(const YYLTYPE&loc , const node *expression , const node *if_body , const node *else_body) :
		if_node(loc , expression , if_body) , else_body_(else_body){}
	~if_else_node() {
		if(else_body_ != nullptr) delete else_body_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *else_body_;
};

#endif

