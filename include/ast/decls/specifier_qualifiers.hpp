#pragma once
#include "../node.hpp"

class type_specifier : public node {
public:
	type_specifier
	(
		const YYLTYPE&loc , const std::string& type_spec
	):
		node(loc),
		type_spec_(type_spec) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const std::string type_spec_;
};

//-----------------------------------------

class type_qualifier : public node {
public:
	type_qualifier
	(
		const YYLTYPE&loc , const std::string& type_qual
	):
		node(loc),
		type_qual_(type_qual) {}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const std::string type_qual_;
};

//----------------------------------------

class storage_class_specifier : public node {
public:
	storage_class_specifier
	(
		const YYLTYPE&loc , const std::string& storage_class_spec
	):
		node(loc),
		storage_class_spec_(storage_class_spec) {}

	void generateIR() const override;
	void printAST(int depth) const override;

	bool decl_spec_typedef_check() const override {
		return (storage_class_spec_ == "TYPEDEF");
	}

private:
	const std::string storage_class_spec_;
};

//---------------------------------------

class function_specifier : public node {
public:
	function_specifier
	(
		const YYLTYPE&loc , const std::string& function_spec
	):
		node(loc),
		function_spec_(function_spec) {}

	~function_specifier(){};

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const std::string function_spec_;
};

//---------------------------------------

class declaration_specifiers : public nodelist {
public:
	declaration_specifiers
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}

	void printAST(int depth) const override;

	//check for presence of typedef storage class specifier;
	bool decl_spec_typedef_check() const override {
		for(int i = 0 ; i < (int)nodes_.size() ; i++) {
			if(nodes_[i]->decl_spec_typedef_check() == true) return true;
			else continue;
		}
		return false;
	}
};

class  type_qualifier_list: public nodelist {
public:
	type_qualifier_list
	(
		const YYLTYPE&loc , std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}

	void printAST(int depth) const override;
};

