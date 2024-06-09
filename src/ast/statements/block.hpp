#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP

#include "../node.hpp"

class block_item_list : public nodelist {
public:
	block_item_list(node *first_node) : nodelist(first_node){}

	void printAST(int depth) const override;
};

#endif
