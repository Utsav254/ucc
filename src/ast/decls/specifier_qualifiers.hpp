#ifndef TYPE_SPECIFIER_HPP
#define TYPE_SPECIFIER_HPP

#include "../node.hpp"

enum class type_specifiers {
	VOID, CHAR, INT, FLOAT, DOUBLE, 
	SHORT, LONG,  
	SIGNED, UNSIGNED,
	STRUCT_OR_UNION,
	ENUM,
	TYPEDEF_NAME,
};

class type_specifier : public node {
public:
	type_specifier(type_specifiers t) : t_(t) {}
	~type_specifier(){};

	void generateIR() const override;
	void printAST(int depth) const override;
	node *clone() const override {
		return new type_specifier(*this);
	}

private:
	type_specifiers t_;
};

//-----------------------------------------

enum class type_qualifiers {
	CONST,
	RESTRICT,
	VOLATILE,
};

class type_qualifier : public node {
public:
	type_qualifier(type_qualifiers q) : q_(q) {}
	~type_qualifier(){};
	node *clone() const override {
		return new type_qualifier(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	type_qualifiers q_;
};

//----------------------------------------

enum class storage_specifiers {
	TYPEDEF,
	EXTERN,
	STATIC,
	AUTO,
	REGISTER,
};

class storage_class_specifier : public node {
public:
	storage_class_specifier(storage_specifiers s) : s_(s) {}
	~storage_class_specifier(){};
	node *clone() const override {
		return new storage_class_specifier(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	storage_specifiers s_;
};

//---------------------------------------

enum class function_specifiers {
	INLINE,
};

class function_specifier : public node {
public:
	function_specifier(function_specifiers f) : f_(f) {}
	~function_specifier(){};
	node *clone() const override {
		return new function_specifier(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	function_specifiers f_;
};

#endif

