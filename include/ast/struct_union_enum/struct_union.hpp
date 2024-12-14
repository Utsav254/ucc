#pragma once
#include "../node.hpp"

class struct_union : public node {
public:
	struct_union
	(
		const YYLTYPE& loc,
		const std::string& su) :
		node(loc),
		su_(su){}

	~struct_union(){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const std::string su_; // struct or union keyword ... 
};

//purely virtual class
class struct_union_spec : public node {
public:
	struct_union_spec
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> struct_union
	):
		node(loc),
		struct_union_(std::move(struct_union)){}

protected:
	std::unique_ptr<node> struct_union_;
};

class struct_union_spec_id : public struct_union_spec {
public:
	struct_union_spec_id
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> struct_union,
		std::unique_ptr<node> identifier
	):
		struct_union_spec(loc , std::move(struct_union)),
		identifier_(std::move(identifier)){}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> identifier_;
};

class struct_union_spec_id_decl : public struct_union_spec_id {
public:
	struct_union_spec_id_decl
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> struct_union,
		std::unique_ptr<node> identifier,
		std::unique_ptr<nodelist> struct_decl_list
	): 
		struct_union_spec_id(loc, std::move(struct_union), std::move(identifier)),
		struct_decl_list_(std::move(struct_decl_list)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<nodelist> struct_decl_list_;
};

class struct_union_spec_decl : public struct_union_spec {
public:
	struct_union_spec_decl
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> struct_union,
		std::unique_ptr<nodelist> struct_decl_list
	):	
		struct_union_spec(loc , std::move(struct_union)),
		struct_decl_list_(std::move(struct_decl_list)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<nodelist> struct_decl_list_;
};

