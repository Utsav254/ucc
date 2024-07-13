#ifndef STRUCT_UNION_DECLS_HPP
#define STRUCT_UNION_DECLS_HPP

#include "../node.hpp"

class struct_declaration : public node {
public:
	struct_declaration(const YYLTYPE& loc , const nodelist *spec_qual_list , const nodelist *struct_decl_list) :
		node(loc),
		spec_qual_list_(spec_qual_list) , struct_decl_list_(struct_decl_list){}
	~struct_declaration() {
		if(spec_qual_list_ != nullptr) delete spec_qual_list_;
		if(struct_decl_list_ != nullptr) delete struct_decl_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *spec_qual_list_;
	const node *struct_decl_list_;
};

class struct_declaration_list : public nodelist {
public:
	struct_declaration_list(const YYLTYPE& loc , node *first_node) : nodelist(loc , first_node){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class struct_declarator : public node {
public:
	struct_declarator(const YYLTYPE& loc , const node *declarator) :
		node(loc),
		declarator_(declarator){}

	~struct_declarator() {
		if(declarator_ != nullptr) delete declarator_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const node *declarator_;
};

class struct_declarator_list : public nodelist {
public:
	struct_declarator_list(const YYLTYPE& loc , node *first_node) : nodelist(loc , first_node){}

	void generateIR() const override;
	void printAST(int depth) const override;
};

class struct_declarator_size : public struct_declarator {
public:
	struct_declarator_size(const YYLTYPE& loc , const node *declarator , const node *constant_expr) :
		struct_declarator(loc , declarator) , constant_expr_(constant_expr){}

	~struct_declarator_size() {
		if(constant_expr_ != nullptr) delete constant_expr_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *constant_expr_;
};

class struct_declarator_padding : public node {
public:
	struct_declarator_padding(const YYLTYPE& loc , const node *constant_expr) :
		node(loc),
		constant_expr_(constant_expr){}

	~struct_declarator_padding() {
		if(constant_expr_ != nullptr) delete constant_expr_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *constant_expr_;
};

#endif


