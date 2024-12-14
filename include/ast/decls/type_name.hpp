#pragma once
#include "ast/node.hpp"

class type_name : public node {
public:
	type_name
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> spec_qual_list
	):
		node(loc) , spec_qual_list_(std::move(spec_qual_list)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> spec_qual_list_;
};

class type_name_abstract : public type_name {
public:
	type_name_abstract
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> spec_qual_list,
		std::unique_ptr<node> abstract_decl
	):
		type_name(loc , std::move(spec_qual_list)),
		abstract_decl_(std::move(abstract_decl)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> abstract_decl_;
};

