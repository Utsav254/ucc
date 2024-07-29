#ifndef ENUM_SPEC_HPP
#define ENUM_SPEC_HPP

#include "ast/node.hpp"

class enum_spec : public node {
public:
	enum_spec(const YYLTYPE& loc , const nodelist *enum_list) :
		node(loc) , enum_list_(enum_list) {}

	~enum_spec() {
		if(enum_list_ != nullptr) delete enum_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const nodelist *enum_list_;
};

class enum_spec_id : public enum_spec {
public:
	enum_spec_id(const YYLTYPE& loc , const node *identifier , const nodelist *enum_list) :
		enum_spec(loc , enum_list) , identifier_(identifier) {}
	~enum_spec_id() {
		if(identifier_ != nullptr) delete identifier_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *identifier_;
};

class enum_declaration : public node {
public:
	enum_declaration(const YYLTYPE& loc , const node *identifier):
		node(loc) , identifier_(identifier) {}

	~enum_declaration() {
		if(identifier_ != nullptr) delete identifier_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *identifier_;
};

#endif
