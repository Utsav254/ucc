#pragma once
#include "../node.hpp"

class block_item_list : public nodelist {
public:
	block_item_list
	(
		const YYLTYPE& loc,
		std::unique_ptr<node> first_node
	):
		nodelist(loc , std::move(first_node)){}

	void printAST(int depth) const override;
	void generateIR() const override;
};

