#pragma once
#include "ast/node.hpp"

class enum_spec : public node {
public:
	enum_spec
	(
		const YYLTYPE& loc,
		std::unique_ptr<nodelist> enum_list) :
		node(loc) , enum_list_(std::move(enum_list)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<nodelist> enum_list_;
};

class enum_spec_id : public enum_spec {
public:
	enum_spec_id
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> identifier,
		std::unique_ptr<nodelist> enum_list
	):
		enum_spec(loc , std::move(enum_list)),
		identifier_(std::move(identifier)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> identifier_;
};

class enum_declaration : public node {
public:
	enum_declaration
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> identifier
	):
		node(loc) , identifier_(std::move(identifier)) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> identifier_;
};

