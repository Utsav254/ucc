#ifndef TYPE_SPECIFIER_HPP
#define TYPE_SPECIFIER_HPP

#include "node.hpp"

enum class types {
	VOID, CHAR, INT, FLOAT, DOUBLE, 
	SHORT, LONG,  
	SIGNED, UNSIGNED,
	STRUCT_OR_UNION,
	ENUM,
	TYPEDEF_NAME,
};

class type_specifier : public node {
public:
	type_specifier(types t) : t_(t) {}
	~type_specifier(){};

	void generateIR() const override;
	void printAST(int depth) const override;
	node *clone() const override {
		return new type_specifier(*this);
	}

private:
	types t_;
};

#endif

