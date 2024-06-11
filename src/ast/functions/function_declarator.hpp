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

	//to be carefuly done since this is relaed to function pointers
	void add_type_temp_typedef_check() const override {
		direct_declarator_->add_type_temp_typedef_check();
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

	//will inherit the function_declarator typedef checker

private:
	nodelist *parameter_list_;
};

class function_declarator_id_list : public function_declarator {
public:

	function_declarator_id_list(node* direct_declarator, nodelist* identifier_list)
        : function_declarator(direct_declarator) , identifier_list_(identifier_list) {}

	~function_declarator_id_list() {
		if(identifier_list_ != nullptr) delete identifier_list_;
	}

	void generateIR() const override;
	void printAST(int depth) const override;

	//typedef_checker would throw a warning...

private:
	nodelist *identifier_list_;
};

#endif
