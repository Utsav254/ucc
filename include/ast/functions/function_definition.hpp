#ifndef FUNCTION_DEFINITION_HPP
#define FUNCTION_DEFINITION_HPP

#include "../node.hpp"

class function_definition : public node {
public:

	function_definition(const YYLTYPE& loc , const node *declaration_specifiers , const node *declarator , const node *compound_statement) :
		node(loc),
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

protected:
    const node *declaration_specifiers_;
	const node *declarator_;
	const node *compound_statement_;
};


class function_definition_decl_list : public function_definition {
public:

	function_definition_decl_list(const YYLTYPE& loc , const node* declaration_specifiers,  
		const node* declarator, const nodelist* declaration_list, const node* compound_statement) :

		function_definition(loc , declaration_specifiers, declarator, compound_statement), 
		declaration_list_(declaration_list) {}

	~function_definition_decl_list() {
		if(declaration_list_ != nullptr) delete declaration_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const nodelist *declaration_list_;
};

#endif
