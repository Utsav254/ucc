#ifndef TYPE_NAME_HPP
#define TYPE_NAME_HPP

#include "ast/node.hpp"

class type_name : public node {
public:
	type_name(const YYLTYPE& loc , const nodelist *spec_qual_list) :
		node(loc) , spec_qual_list_(spec_qual_list) {}

	~type_name() {
		if(spec_qual_list_ != nullptr) delete spec_qual_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const nodelist *spec_qual_list_;
};

class type_name_abstract : public type_name {
public:
	type_name_abstract(const YYLTYPE& loc , const nodelist *spec_qual_list , const node *abstract_decl) :
		type_name(loc , spec_qual_list)  , abstract_decl_(abstract_decl) {}

	~type_name_abstract() {
		if(spec_qual_list_ != nullptr) delete abstract_decl_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *abstract_decl_;
};


#endif
