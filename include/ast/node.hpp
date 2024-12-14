#pragma once
#include <typeinfo>
#include <vector>
#include <string>
#include <memory>
#include "locations.hpp"

struct YYLTYPE;

class node {
public:

	node(const YYLTYPE& loc) : loc_(loc) {}

	virtual ~node() {};

	virtual void generateIR() const = 0;

	virtual void printAST(int depth) const = 0;

	virtual const std::type_info& get_node_type() const final {
		return typeid(*this);
	}

	//functions for tracking typedef declarations:
	virtual bool decl_spec_typedef_check() const {return false;}
	virtual void add_type_temp_typedef_check() const { return; }

	//will possibly need the following:
	//getsize()
	//gettype()
	//interpret() ?
	//ispointer()
	//getarrlen
	//
	//--context based functions--
	//create_param_map()
	//create_var_map()
	//
	//--possibly some kind of search or iterate function?
protected:
	const YYLTYPE loc_;
};

class nodelist : public node {
public: 
	nodelist(const YYLTYPE& loc , std::unique_ptr<node> first_node) : node(loc)
	{
		nodes_.push_back(std::move(first_node));
	}	

	void generateIR() const override;
	void printAST(int depth) const override;

	void pushback(std::unique_ptr<node> next);

protected:
	std::vector <std::unique_ptr<node>> nodes_;
};





//parsing function to be defined the parser.y file
extern std::unique_ptr<node> parseAST(std::string sourcepath);

//global root node of ast:
extern std::unique_ptr<node> root_node;

