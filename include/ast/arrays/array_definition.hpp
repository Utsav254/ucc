#pragma once
#include "../node.hpp"

class array_definition : public node {
public:
	array_definition
	(
		const YYLTYPE&loc , std::unique_ptr<node> direct_declarator
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

class array_definition_size : public array_definition {
public:
	array_definition_size
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> direct_declarator,
		std::unique_ptr<node> assignment_expression
	):
		array_definition(loc , std::move(direct_declarator)) , 
		assignment_expression_(std::move(assignment_expression)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

	//will inherit the typedef checker of array defintion

protected: 
	std::unique_ptr<node> assignment_expression_;
};

class array_definition_type_qual : public array_definition {
public:
	array_definition_type_qual
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> direct_declarator,
		std::unique_ptr<node> type_qualifier_list
	):
		array_definition(loc , std::move(direct_declarator)),
		type_qualifier_list_(std::move(type_qualifier_list)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> type_qualifier_list_;
};

class array_definition_type_qual_size : public array_definition_size {
public:
	array_definition_type_qual_size
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> direct_declarator,
		std::unique_ptr<node> type_qualifier_list,
		std::unique_ptr<node> assignment_expr
	):
		array_definition_size(loc , std::move(direct_declarator) , std::move(assignment_expr)),
		type_qualifier_list_(std::move(type_qualifier_list)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node>  type_qualifier_list_;
};

