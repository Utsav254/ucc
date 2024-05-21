#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include <string>
#include "node.hpp"

class identifier : public node {
public:
	identifier(std::string id) : identifier_(id) {};
	~identifier(){};

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::string identifier_;
};

#endif
