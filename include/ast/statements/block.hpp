#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP

#include "../node.hpp"

class block_item_list : public nodelist {
public:
	block_item_list(const YYLTYPE& loc , node *first_node) : nodelist(loc , first_node){}

	void printAST(int depth) const override;
};

#endif
