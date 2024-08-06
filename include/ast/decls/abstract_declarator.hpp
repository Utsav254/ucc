#ifndef ABSTRACT_DECLARATOR_HPP
#define ABSTRACT_DECLARATOR_HPP

#include "ast/node.hpp"

class abstract_declarator : public node {
public:
	abstract_declarator(const YYLTYPE& loc , const node *abstract_direct_decl) : 
		node(loc) , abstract_direct_decl_(abstract_direct_decl) {}

	~abstract_declarator() {
		if(abstract_direct_decl_ != nullptr) delete abstract_direct_decl_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const node *abstract_direct_decl_;
};


class abstract_declarator_pointer : public abstract_declarator {
public:
	abstract_declarator_pointer(const YYLTYPE& loc , const nodelist *pointer , const node *abstract_direct_decl) : 
		abstract_declarator(loc , abstract_direct_decl) , pointer_(pointer) {}

	~abstract_declarator_pointer() {
		if(pointer_ != nullptr) delete pointer_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const nodelist *pointer_;
};


#endif
