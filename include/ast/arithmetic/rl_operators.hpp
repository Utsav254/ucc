#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include "../node.hpp"

class rl_op : public node {
public:
	rl_op(const YYLTYPE& loc , const node *l_value , const node *r_value) :
		node(loc),
		l_value_(l_value) , r_value_(r_value) {}

	~rl_op() {
		if(l_value_ != nullptr) delete l_value_;
		if(r_value_ != nullptr) delete r_value_;
	}

protected:
	const node *l_value_;
	const node *r_value_;
};

class add : public rl_op{
public:
	add(const YYLTYPE& loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class sub : public rl_op{
public:
	sub(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};


class mul : public rl_op{
public:
	mul(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class divi : public rl_op{
public:
	divi(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class modulo : public rl_op{
public:
	modulo(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class left_shift: public rl_op{
public:
	left_shift(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class right_shift: public rl_op{
public:
	right_shift(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class less_than: public rl_op{
public:
	less_than(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class greater_than: public rl_op{
public:
	greater_than(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class less_eq_than: public rl_op{
public:
	less_eq_than(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class greater_eq_than: public rl_op{
public:
	greater_eq_than(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class equality: public rl_op{
public:
	equality(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class not_equal: public rl_op{
public:
	not_equal(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class andop: public rl_op{
public:
	andop(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class xorop: public rl_op{
public:
	xorop(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class orop: public rl_op{
public:
	orop(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class log_andop: public rl_op{
public:
	log_andop(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

class log_orop: public rl_op{
public:
	log_orop(const YYLTYPE&loc , const node *l_value , const node *r_value) :
		rl_op(loc , l_value , r_value){}

	void generateIR() const override;
	void printAST(int depth) const override;

};

#endif
