#ifndef JUMPS_HPP
#define JUMPS_HPP

#include "../node.hpp"

class jump_statement_goto : public node {
public:
	jump_statement_goto(const YYLTYPE&loc , const node *identifier) :
		node(loc),
		identifier_(identifier){}

	~jump_statement_goto() {
		if(identifier_ != nullptr) delete identifier_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *identifier_;
};

class jump_statement_continue : public node {
public:
	jump_statement_continue(const YYLTYPE&loc) : node(loc) {}
	~jump_statement_continue(){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class jump_statement_break : public node {
public:
	jump_statement_break(const YYLTYPE&loc) : node(loc) {}
	~jump_statement_break(){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class jump_statement_ret : public node {
public:
	jump_statement_ret(const YYLTYPE&loc) : node(loc) {}
	~jump_statement_ret(){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class jump_statement_ret_expr: public node {
public:
	jump_statement_ret_expr(const YYLTYPE&loc , const node *expression) :
		node(loc),
		expression_(expression){}

	~jump_statement_ret_expr() {
		if(expression_ != nullptr) delete expression_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *expression_;
};

class goto_target : public node {
public:
	goto_target(const YYLTYPE&loc , const node *identifier , const node *statement) :
		node(loc),
		identifier_(identifier) , statement_(statement){}
	~goto_target() {
		if(identifier_ != nullptr) delete identifier_;
		if(statement_ != nullptr) delete statement_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *identifier_;
	const node *statement_;
};

#endif
