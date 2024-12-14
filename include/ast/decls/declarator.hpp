#pragma once
#include "../node.hpp"

class declarator : public node {
public:
	declarator
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> direct_declarator
	):
		node(loc),
		direct_declarator_(std::move(direct_declarator)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

	void add_type_temp_typedef_check() const override {
		direct_declarator_->add_type_temp_typedef_check();
	}

protected: 
	std::unique_ptr<node> direct_declarator_;
};

class init_declarator : public node {
public:
	init_declarator
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> declarator
	):
		node(loc),
		declarator_(std::move(declarator)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

	void add_type_temp_typedef_check() const override {
		declarator_->add_type_temp_typedef_check();
	}

protected: 
	std::unique_ptr<node> declarator_;
};

class init_declarator_ini : public init_declarator {
public:
	init_declarator_ini
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> declarator,
		std::unique_ptr<node> initialiser
	): 
		init_declarator(loc , std::move(declarator)),
		initialiser_(std::move(initialiser)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> initialiser_;
};


