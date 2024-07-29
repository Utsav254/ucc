#ifndef STRUCT_UNION_HPP
#define STRUCT_UNION_HPP

#include "../node.hpp"

class struct_union : public node {
public:
	struct_union(const YYLTYPE& loc , const std::string su) :
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
	struct_union_spec(const YYLTYPE& loc , const node *struct_union) :
		node(loc),
		struct_union_(struct_union){}

	~struct_union_spec() {
		if(struct_union_ != nullptr) delete struct_union_;
	}

protected:
	const node *struct_union_;
};


class struct_union_spec_id : public struct_union_spec {
public:
	struct_union_spec_id(const YYLTYPE& loc , const node *struct_union , const node *identifier) :
		struct_union_spec(loc , struct_union) , identifier_(identifier){}

	~struct_union_spec_id() {
		if(identifier_ != nullptr) delete identifier_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const node *identifier_;
};

class struct_union_spec_id_decl : public struct_union_spec_id {
public:
	struct_union_spec_id_decl(const YYLTYPE& loc , const node *struct_union , const node *identifier , const nodelist *struct_decl_list) : 
		struct_union_spec_id(loc , struct_union , identifier),
		struct_decl_list_(struct_decl_list){}

	~struct_union_spec_id_decl() {
		if(struct_decl_list_ != nullptr) delete struct_decl_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const nodelist *struct_decl_list_;
};

class struct_union_spec_decl : public struct_union_spec {
public:
	struct_union_spec_decl(const YYLTYPE& loc , const node *struct_union , const nodelist *struct_decl_list) :	
		struct_union_spec(loc , struct_union) , struct_decl_list_(struct_decl_list){}
	~struct_union_spec_decl() {
		if(struct_decl_list_ != nullptr) delete struct_decl_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const nodelist *struct_decl_list_;
};

#endif

