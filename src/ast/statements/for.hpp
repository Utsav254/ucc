#ifndef FOR_HPP
#define FOR_HPP

#include "../node.hpp"

class for_node : public node {
public:


protected:
	node *declaration_;
	node *condition_expr_;
	node *statement_;
};

class for_node_mod : public for_node {
public:


private:
	node *modifying_expr_;
};

//------------------------------------------

class for_node_ext : public node {
public:


protected:
	node *initial_expr_;
	node *condition_expr_;
	node *statement_;
};

class for_node_ext_mod : public for_node_ext {
public:


private:
	node *modifying_expr_;
};

#endif

