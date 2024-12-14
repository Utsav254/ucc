#pragma once
#include "../node.hpp"

class function_declarator : public node {
public:

	function_declarator
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> direct_declarator
	): 
		node(loc),
		direct_declarator_(std::move(direct_declarator)){}

	void generateIR() const override;
	void printAST(int depth) const override;

	//to be carefuly done since this is relaed to function pointers
	void add_type_temp_typedef_check() const override {
		direct_declarator_->add_type_temp_typedef_check();
	}

protected:
	std::unique_ptr<node> direct_declarator_;
};

class function_declarator_param : public function_declarator {
public:

	function_declarator_param
	(
		const YYLTYPE&loc,
		std::unique_ptr<node>  direct_declarator,
		std::unique_ptr<node>  parameter_list
	):
		function_declarator(loc , std::move(direct_declarator)),
		parameter_list_(std::move(parameter_list)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> parameter_list_;
};

class function_declarator_id_list : public function_declarator {
public:

	function_declarator_id_list
	(
		const YYLTYPE&loc,
		std::unique_ptr<node>  direct_declarator,
		std::unique_ptr<node>  identifier_list
	):
		function_declarator(loc , std::move(direct_declarator)),
		identifier_list_(std::move(identifier_list)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> identifier_list_;
};

