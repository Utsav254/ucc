#ifndef FUNCTION_DECLERATOR_HPP
#define FUNCTION_DECLERATOR_HPP

#include "../node.hpp"

class function_declarator : public node {
public:

	function_declarator(node *direct_declarator) : direct_declarator_(direct_declarator){}

	~function_declarator() {
		if(direct_declarator_ != nullptr) delete direct_declarator_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;
	node *clone() const override {
		return new function_declarator(*this);
	}

protected:
	node *direct_declarator_;
};


class function_declarator_param : public function_declarator {
public:

	function_declarator_param(node* direct_declarator, nodelist* parameter_list)
        : function_declarator(direct_declarator) , parameter_list_(parameter_list) {}

	~function_declarator_param() {
		if(parameter_list_ != nullptr) delete parameter_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;
	node *clone() const override {
		return new function_declarator_param(*this);
	}

private:
	nodelist *parameter_list_;
};

#endif
