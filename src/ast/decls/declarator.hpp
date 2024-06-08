#ifndef DECLARATOR_HPP
#define DECLARATOR_HPP

#include "../node.hpp"

class declarator : public node {
public:
	declarator(node *direct_declarator) : direct_declarator_(direct_declarator) {}
	~declarator() {
		if(direct_declarator_ != nullptr) delete direct_declarator_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected: 
	node *direct_declarator_;
};

class declarator_pointer : public declarator {
public:
	declarator_pointer(node *pointer , node *direct_declarator) : 
		declarator(direct_declarator) , pointer_(pointer) {}
	~declarator_pointer() {
		if(pointer_ != nullptr) delete pointer_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *pointer_;
};

class init_declarator : public node {
public:
	init_declarator(node *declarator) : declarator_(declarator) {}
	~init_declarator() {
		if(declarator_ != nullptr) delete declarator_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected: 
	node *declarator_;
};

class init_declarator_ini : public init_declarator {
public:
	init_declarator_ini(node *declarator , node *initialiser) : 
		init_declarator(declarator) , initialiser_(initialiser) {}

	~init_declarator_ini() {
		if(initialiser_ != nullptr) delete initialiser_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *initialiser_;
};



#endif
