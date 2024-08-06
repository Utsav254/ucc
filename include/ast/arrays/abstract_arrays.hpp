#ifndef ABSTRACT_ARRAYS_HPP
#define ABSTRACT_ARRAYS_HPP

#include "ast/node.hpp"

class unamed_empty_array : public node {
public:
	unamed_empty_array(const YYLTYPE& loc) :
		node(loc) {}

	~unamed_empty_array() = default;

	void generateIR() const override;
	void printAST(int depth) const override;

};

class unamed_empty_array_size : public unamed_empty_array {
public:
	unamed_empty_array_size(const YYLTYPE& loc , const node *assignment_expr) :
		unamed_empty_array(loc)  , assignment_expr_(assignment_expr){}

	~unamed_empty_array_size() {
		if(assignment_expr_ != nullptr) delete assignment_expr_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const node *assignment_expr_;
};

class array_decl_abstract : public unamed_empty_array {
public:
	array_decl_abstract(const YYLTYPE& loc , const node *direct_abstract_decl) :
		unamed_empty_array(loc)  , direct_abstract_decl_(direct_abstract_decl){}

	~array_decl_abstract() {
		if(direct_abstract_decl_ != nullptr) delete direct_abstract_decl_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *direct_abstract_decl_;
};

class array_decl_abstract_size : public unamed_empty_array_size {
public:
	array_decl_abstract_size(const YYLTYPE& loc , const node *direct_abstract_decl , const node *assignment_expr) :
		unamed_empty_array_size(loc , assignment_expr)  , direct_abstract_decl_(direct_abstract_decl){}

	~array_decl_abstract_size() {
		if(direct_abstract_decl_ != nullptr) delete direct_abstract_decl_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *direct_abstract_decl_;
};


#endif
