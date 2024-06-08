#ifndef STRUCT_UNION_DECLS_HPP
#define STRUCT_UNION_DECLS_HPP

#include "../node.hpp"

class struct_declaration : public node {
public:
	struct_declaration(nodelist *spec_qual_list , nodelist *struct_decl_list) :
		spec_qual_list_(spec_qual_list) , struct_decl_list_(struct_decl_list){}
	~struct_declaration() {
		if(spec_qual_list_ != nullptr) delete spec_qual_list_;
		if(struct_decl_list_ != nullptr) delete struct_decl_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *spec_qual_list_;
	node *struct_decl_list_;
};

class struct_declarator : public node {
public:
	struct_declarator(node *declarator) : declarator_(declarator){}	
	~struct_declarator() {
		if(declarator_ != nullptr) delete declarator_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	node *declarator_;
};

class struct_declarator_size : public struct_declarator {
public:
	struct_declarator_size(node *declarator , node *constant_expr) :
		struct_declarator(declarator) , constant_expr_(constant_expr){}
	~struct_declarator_size() {
		if(constant_expr_ != nullptr) delete constant_expr_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *constant_expr_;
};

class struct_declarator_padding : public node {
public:
	struct_declarator_padding(node *constant_expr) : constant_expr_(constant_expr){}
	~struct_declarator_padding() {
		if(constant_expr_ != nullptr) delete constant_expr_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *constant_expr_;
};

#endif


