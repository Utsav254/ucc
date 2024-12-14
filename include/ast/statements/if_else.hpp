#pragma once
#include "../node.hpp"

class if_node : public node {
public:
	if_node
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> expression,
		std::unique_ptr<node> if_body
	):
		node(loc),
		expression_(std::move(expression)),
		if_body_(std::move(if_body)){}

	void generateIR() const override;
	void printAST(int depth) const override;

protected:
	std::unique_ptr<node> expression_;
	std::unique_ptr<node> if_body_;
};

class if_else_node : public if_node {
public:
	if_else_node
	(
		const YYLTYPE&loc,
		std::unique_ptr<node> expression,
		std::unique_ptr<node> if_body,
		std::unique_ptr<node> else_body
	):
		if_node(loc, std::move(expression), std::move(if_body)),
		else_body_(std::move(else_body)){}

	void generateIR() const override;
	void printAST(int depth) const override;

private:
	std::unique_ptr<node> else_body_;
};

