#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include "../node.hpp"

class rl_op : public node {
public:
	rl_op(node *l_value , node *r_value) : l_value_(l_value) , r_value_(r_value) {}
	~rl_op() {
		if(l_value_ != nullptr) delete l_value_;
		if(r_value_ != nullptr) delete r_value_;
	}

protected:
	node *l_value_;
	node *r_value_;
};

class add : public rl_op{
public:
	add(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new add(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class sub : public rl_op{
public:
	sub(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new sub(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};


class mul : public rl_op{
public:
	mul(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new mul(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class divi : public rl_op{
public:
	divi(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new divi(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class modulo : public rl_op{
public:
	modulo(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new modulo(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class left_shift: public rl_op{
public:
	left_shift(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new left_shift(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class right_shift: public rl_op{
public:
	right_shift(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new right_shift(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class less_than: public rl_op{
public:
	less_than(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new less_than(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class greater_than: public rl_op{
public:
	greater_than(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new greater_than(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class less_eq_than: public rl_op{
public:
	less_eq_than(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new less_eq_than(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class greater_eq_than: public rl_op{
public:
	greater_eq_than(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new greater_eq_than(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class equality: public rl_op{
public:
	equality(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new equality(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class not_equal: public rl_op{
public:
	not_equal(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new not_equal(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class andop: public rl_op{
public:
	andop(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new andop(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class xorop: public rl_op{
public:
	xorop(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new xorop(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class orop: public rl_op{
public:
	orop(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new orop(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class log_andop: public rl_op{
public:
	log_andop(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new log_andop(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

class log_orop: public rl_op{
public:
	log_orop(node *l_value , node *r_value) : rl_op(l_value , r_value){}
	node *clone() const override {
		return new log_orop(*this);
	}
	void generateIR() const override;
	void printAST(int depth) const override;

};

#endif
