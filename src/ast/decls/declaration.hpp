#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include "../node.hpp"

class declaration : public node {
public:
	declaration(node *declaration_specifier) : declaration_specifier_(declaration_specifier) {}
	~declaration() {
		if(declaration_specifier_ != nullptr) delete declaration_specifier_;
	}
	node *clone() const override {
		return new declaration(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	node *declaration_specifier_;
};

class declaration_init_decl : public declaration {
public:
	declaration_init_decl(node *declaration_specifier , nodelist *init_decl_list) : 
		declaration(declaration_specifier),
		init_decl_list_(init_decl_list) {}
	~declaration_init_decl() {
		if(init_decl_list_ != nullptr) delete init_decl_list_;
	}
	node *clone() const override {
		return new declaration_init_decl(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private: 
	nodelist *init_decl_list_;
};

#endif
