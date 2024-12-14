#pragma once
#include "../node.hpp"

class function_definition : public node {
public:

	function_definition
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> declaration_specifiers,
		std::unique_ptr<node> declarator,
		std::unique_ptr<node> compound_statement
	):
		node(loc),
		declaration_specifiers_(std::move(declaration_specifiers)),
		declarator_(std::move(declarator)), 
		compound_statement_(std::move(compound_statement)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> declaration_specifiers_;
	std::unique_ptr<node> declarator_;
	std::unique_ptr<node> compound_statement_;
};


class function_definition_decl_list : public function_definition {
public:

	function_definition_decl_list
	(
		const YYLTYPE& loc,
		std::unique_ptr<node>  declaration_specifiers,
		std::unique_ptr<node>  declarator,
		std::unique_ptr<nodelist>  declaration_list,
		std::unique_ptr<node>  compound_statement) :

		function_definition(loc , std::move(declaration_specifiers), std::move(declarator), std::move(compound_statement)), 
		declaration_list_(std::move(declaration_list)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> declaration_list_;
};

