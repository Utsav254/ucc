#ifndef JUMPS_HPP
#define JUMPS_HPP

#include "../node.hpp"

enum class jump_type {
	GOTO,
	CONTINUE,
	BREAK,
	RETURN,
};

class jump_statement : public node {
public:
	jump_statement(jump_type j) : j_(j){}
	~jump_statement() {}
	node *clone() const override {
		return new jump_statement(*this);
	}
	
	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	jump_type j_;
};

class jump_statement_goto : public jump_statement {
public:
	jump_statement_goto(jump_type j , node *identifier) :
		jump_statement(j),
		identifier_(identifier){}

	~jump_statement_goto() {
		if(identifier_ != nullptr) delete identifier_;
	}
	node *clone() const override {
		return new jump_statement_goto(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *identifier_;
};

class jump_statement_ret_expr: public jump_statement {
public:
	jump_statement_ret_expr(jump_type j , node *expression) :
		jump_statement(j),
		expression_(expression){}

	~jump_statement_ret_expr() {
		if(expression_ != nullptr) delete expression_;
	}
	node *clone() const override {
		return new jump_statement_ret_expr(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *expression_;
};

class goto_target : public node {
public:
	goto_target(node *identifier , node *statement) : 
		identifier_(identifier) , statement_(statement){}
	~goto_target() {
		if(identifier_ != nullptr) delete identifier_;
		if(statement_ != nullptr) delete statement_;
	}
	node *clone() const override {
		return new goto_target(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *identifier_;
	node *statement_;
};

#endif
