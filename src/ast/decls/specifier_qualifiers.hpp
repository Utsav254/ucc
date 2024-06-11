#ifndef TYPE_SPECIFIER_HPP
#define TYPE_SPECIFIER_HPP

#include "../node.hpp"


class type_specifier : public node {
public:
	type_specifier(std::string type_spec) : type_spec_(type_spec) {}
	~type_specifier(){};

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::string type_spec_;
};

//-----------------------------------------

class type_qualifier : public node {
public:
	type_qualifier(std::string type_qual) : type_qual_(type_qual) {}
	~type_qualifier(){};

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::string type_qual_;
};

//----------------------------------------

class storage_class_specifier : public node {
public:
	storage_class_specifier(std::string storage_class_spec) : storage_class_spec_(storage_class_spec) {}
	~storage_class_specifier(){};

	void generateIR() const override;
	void printAST(int depth) const override;

	bool decl_spec_typedef_check() const override {
		return (storage_class_spec_ == "TYPEDEF");
	}

private:
	std::string storage_class_spec_;
};

//---------------------------------------

class function_specifier : public node {
public:
	function_specifier(std::string function_spec) : function_spec_(function_spec) {}
	~function_specifier(){};

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::string function_spec_;
};

//---------------------------------------

class declaration_specifiers : public nodelist {
public:
	declaration_specifiers(node *first_node) : nodelist(first_node){}

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
	type_qualifier_list(node *first_node) : nodelist(first_node){}

	void printAST(int depth) const override;
};

#endif

