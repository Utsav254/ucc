#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include "../node.hpp"

class rl_op : public node {
public:
	rl_op(node *rvalue , node *lvalue) : rvalue_(rvalue) , lvalue_(lvalue) {}
	~rl_op() {
		if(rvalue_ != nullptr) delete rvalue_;
		if(lvalue_ != nullptr) delete lvalue_;
	}

protected:
	node *rvalue_;
	node *lvalue_;
};

class add : public rl_op{
public:
	add(node *rvalue , node *lvalue) : rl_op(rvalue , lvalue){}
	node *clone() const override {
		return new add(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class sub : public rl_op{
public:
	sub(node *rvalue , node *lvalue) : rl_op(rvalue , lvalue){}
	node *clone() const override {
		return new sub(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};


class mul : public rl_op{
public:
	mul(node *rvalue , node *lvalue) : rl_op(rvalue , lvalue){}
	node *clone() const override {
		return new mul(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class div : public rl_op{
public:
	div(node *rvalue , node *lvalue) : rl_op(rvalue , lvalue){}
	node *clone() const override {
		return new div(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class modulo : public rl_op{
public:
	modulo(node *rvalue , node *lvalue) : rl_op(rvalue , lvalue){}
	node *clone() const override {
		return new modulo(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class left_shift: public rl_op{
public:
	left_shift(node *rvalue , node *lvalue) : rl_op(rvalue , lvalue){}
	node *clone() const override {
		return new left_shift(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class right_shift: public rl_op{
public:
	right_shift(node *rvalue , node *lvalue) : rl_op(rvalue , lvalue){}
	node *clone() const override {
		return new right_shift(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};














#endif
