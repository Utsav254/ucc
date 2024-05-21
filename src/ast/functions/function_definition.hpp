#ifndef FUNCTION_DEFINITION_HPP
#define FUNCTION_DEFINITION_HPP

#include "../node.hpp"

class function_definition : public node {
public:

	function_definition(node *declaration_specifiers , node *declarator , node *compound_statement) : 
		declaration_specifiers_(declaration_specifiers),
		declarator_(declarator), 
		compound_statement_(compound_statement) {}

	~function_definition() {
		if(declaration_specifiers_ != nullptr) delete declaration_specifiers_;
		if(declarator_ != nullptr) delete declarator_;
		if(compound_statement_ != nullptr) delete compound_statement_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;
	node *clone() const override {
		return new function_definition(*this);
	}

protected:
    node *declaration_specifiers_;
	node *declarator_;
	node *compound_statement_;
};


class function_definition_decl_list : public function_definition {
public:

	function_definition_decl_list(node* declaration_specifiers, node* declarator, nodelist* declaration_list, node* compound_statement)
        : function_definition(declaration_specifiers, declarator, compound_statement), declaration_list_(declaration_list) {}

	~function_definition_decl_list() {
		if(declaration_specifiers_ != nullptr) delete declaration_specifiers_;
		if(declarator_ != nullptr) delete declarator_;
		if(declaration_list_ != nullptr) delete declaration_list_;
		if(compound_statement_ != nullptr) delete compound_statement_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;
	node *clone() const override {
		return new function_definition_decl_list(*this);
	}

private:
	nodelist *declaration_list_;
};

#endif
