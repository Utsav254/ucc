#ifndef FOR_HPP
#define FOR_HPP

#include "../node.hpp"

class for_node : public node {
public:
	for_node(const YYLTYPE& loc , const node *declaration , const node *condition_expr , const node *statement):
		node(loc),
		declaration_(declaration) , condition_expr_(condition_expr) , statement_(statement){}

	~for_node() {
		if(declaration_ != nullptr) delete declaration_;
		if(condition_expr_ != nullptr) delete condition_expr_;
		if(statement_ != nullptr) delete statement_;
	}
	
	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const node *declaration_;
	const node *condition_expr_;
	const node *statement_;
};
//------
class for_node_mod : public for_node {
public:
	for_node_mod(const YYLTYPE& loc , const node *declaration , const node *condition_expr , const node *statement , const node *modifying_expr) :
		for_node(loc , declaration , condition_expr , statement) , modifying_expr_(modifying_expr){}

	~for_node_mod() {
		if(modifying_expr_ != nullptr) delete modifying_expr_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *modifying_expr_;
};

//------------------------------------------

class for_node_ext : public node {
public:
	for_node_ext(const YYLTYPE& loc , const node *initial_expr , const node *condition_expr , const node *statement) :
		node(loc),
		initial_expr_(initial_expr) , condition_expr_(condition_expr) , statement_(statement){}

	~for_node_ext() {
		if(initial_expr_ != nullptr) delete initial_expr_;
		if(condition_expr_ != nullptr) delete condition_expr_;
		if(statement_ != nullptr) delete statement_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	const node *initial_expr_;
	const node *condition_expr_;
	const node *statement_;
};
//------
class for_node_ext_mod : public for_node_ext {
public:
	for_node_ext_mod(const YYLTYPE& loc , const node *initial_expr , const node *condition_expr , const node *statement , const node *modifying_expr) :
		for_node_ext(loc , initial_expr , condition_expr , statement) , modifying_expr_(modifying_expr){}
	~for_node_ext_mod() {
		if(modifying_expr_ != nullptr) delete modifying_expr_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	const node *modifying_expr_;
};

#endif

