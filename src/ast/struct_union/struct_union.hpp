#ifndef STRUCT_UNION_HPP
#define STRUCT_UNION_HPP

#include "../node.hpp"

class struct_union : public node {
public:
	struct_union(std::string su) : su_(su){}
	~struct_union(){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::string su_;
};

//purely virtual class
class struct_union_spec : public node {
public:
	struct_union_spec(node *struct_union) : struct_union_(struct_union){}
	~struct_union_spec() {
		if(struct_union_ != nullptr) delete struct_union_;
	}

protected:
	node *struct_union_;
};



class struct_union_spec_id : public struct_union_spec {
public:
	struct_union_spec_id(node *struct_union , node *identifier) :
		struct_union_spec(struct_union) , identifier_(identifier){}
	~struct_union_spec_id() {
		if(identifier_ != nullptr) delete identifier_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	node *identifier_;
};

class struct_union_spec_id_decl : public struct_union_spec_id {
public:
	struct_union_spec_id_decl(node *struct_union , node *identifier , nodelist *struct_decl_list) : 
		struct_union_spec_id(struct_union , identifier) , 
		struct_decl_list_(struct_decl_list){}
	~struct_union_spec_id_decl() {
		if(struct_decl_list_ != nullptr) delete struct_decl_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	nodelist *struct_decl_list_;
};

class struct_union_spec_decl : public struct_union_spec {
public:
	struct_union_spec_decl(node *struct_union , nodelist *struct_decl_list) : 
		struct_union_spec(struct_union) , struct_decl_list_(struct_decl_list){}
	~struct_union_spec_decl() {
		if(struct_decl_list_ != nullptr) delete struct_decl_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	nodelist *struct_decl_list_;
};

#endif

