#ifndef DECLARATION_SPECIFIER_HPP
#define DECLARATION_SPECIFIER_HPP

#include "node.hpp"
#include "../cli.hpp"

class declaration_specifier : public node {
public:
	declaration_specifier(node *main_specifier) : main_specifier_(main_specifier) {}

	~declaration_specifier(){
		if(main_specifier_ != nullptr) delete main_specifier_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;
	node *clone() const override {
		return new declaration_specifier(*this);
	}
	
	node *fetch_main_spec() {
		return main_specifier_;
	}

private:
	node *main_specifier_;
};

class declaration_specifier_double : public node {
public:
	declaration_specifier_double(node *modifying_specifier , node * prev_decl_spec) : modifying_specifier_(modifying_specifier) {
		declaration_specifier *ds_ptr = dynamic_cast<declaration_specifier*>(prev_decl_spec);
		if(ds_ptr == nullptr) die("Unexpected dynamic cast failed...yet to handle" , errcode::INTERNAL);
		node *temp = ds_ptr->fetch_main_spec();
		main_specifier_ = temp->clone();

		delete ds_ptr;
	}

	~declaration_specifier_double(){
		if(modifying_specifier_ != nullptr) delete modifying_specifier_;
		if(main_specifier_ != nullptr) delete main_specifier_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;
	node *clone() const override {
		return new declaration_specifier_double(*this);
	}

private:
	node *main_specifier_;
	node *modifying_specifier_;
};

#endif
