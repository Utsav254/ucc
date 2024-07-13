#ifndef DECLARATOR_HPP
#define DECLARATOR_HPP

#include "../node.hpp"

class declarator : public node {
public:
	declarator(const YYLTYPE&loc , const node *direct_declarator) :
		node(loc),
		direct_declarator_(direct_declarator) {}

	~declarator() {
		if(direct_declarator_ != nullptr) delete direct_declarator_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

	void add_type_temp_typedef_check() const override {
		direct_declarator_->add_type_temp_typedef_check();
	}

protected: 
	const node *direct_declarator_;
};

class init_declarator : public node {
public:
	init_declarator(const YYLTYPE&loc , const node *declarator) :
		node(loc),
		declarator_(declarator) {}

	~init_declarator() {
		if(declarator_ != nullptr) delete declarator_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

	void add_type_temp_typedef_check() const override {
		declarator_->add_type_temp_typedef_check();
	}

protected: 
	const node *declarator_;
};

class init_declarator_ini : public init_declarator {
public:
	init_declarator_ini(const YYLTYPE&loc , const node *declarator , const node *initialiser) : 
		init_declarator(loc , declarator) , initialiser_(initialiser) {}

	~init_declarator_ini() {
		if(initialiser_ != nullptr) delete initialiser_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *initialiser_;
};



#endif
