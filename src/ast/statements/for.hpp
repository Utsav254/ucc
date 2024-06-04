#ifndef FOR_HPP
#define FOR_HPP

#include "../node.hpp"

class for_node : public node {
public:
	for_node(node *declaration , node *condition_expr , node *statement):
		declaration_(declaration) , condition_expr_(condition_expr) , statement_(statement){}
	~for_node() {
		if(declaration_ != nullptr) delete declaration_;
		if(condition_expr_ != nullptr) delete condition_expr_;
		if(statement_ != nullptr) delete statement_;
	}
	node *clone() const override {
		return new for_node(*this);
	}
	
	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	node *declaration_;
	node *condition_expr_;
	node *statement_;
};
//------
class for_node_mod : public for_node {
public:
	for_node_mod(node *declaration , node *condition_expr , node *statement , node *modifying_expr):
		for_node(declaration , condition_expr , statement) , modifying_expr_(modifying_expr){}
	~for_node_mod() {
		if(modifying_expr_ != nullptr) delete modifying_expr_;
	}
	node *clone() const override {
		return new for_node_mod(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *modifying_expr_;
};

//------------------------------------------

class for_node_ext : public node {
public:
	for_node_ext(node *initial_expr , node *condition_expr , node *statement):
		initial_expr_(initial_expr) , condition_expr_(condition_expr) , statement_(statement){}
	~for_node_ext() {
		if(initial_expr_ != nullptr) delete initial_expr_;
		if(condition_expr_ != nullptr) delete condition_expr_;
		if(statement_ != nullptr) delete statement_;
	}
	node *clone() const override {
		return new for_node_ext(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	node *initial_expr_;
	node *condition_expr_;
	node *statement_;
};
//------
class for_node_ext_mod : public for_node_ext {
public:
	for_node_ext_mod(node *initial_expr , node *condition_expr , node *statement , node *modifying_expr):
		for_node_ext(initial_expr , condition_expr , statement) , modifying_expr_(modifying_expr){}
	~for_node_ext_mod() {
		if(modifying_expr_ != nullptr) delete modifying_expr_;
	}
	node *clone() const override {
		return new for_node_ext_mod(*this);
	}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	node *modifying_expr_;
};

#endif

