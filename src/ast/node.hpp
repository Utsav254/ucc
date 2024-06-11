#ifndef NODE_HPP
#define NODE_HPP

#include <typeinfo>
#include <vector>
#include <string>

class node {
public:

	node(){};

	virtual ~node(){};

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

};

class nodelist : public node {

public: 
	nodelist(node *first_node) : nodes_({first_node}){}
	~nodelist() {
		for(int i = 0 ; i < (int)nodes_.size() ; i++) {
			delete nodes_[i];
		}
	}

	void generateIR() const override;
	void printAST(int depth) const override;

	void pushback(node *next);

protected:
	std::vector <node*> nodes_;
};


//parsing function to be defined the parser.y file
extern node *parseAST(std::string sourcepath);

//global root node of ast:
extern node *root_node;

#endif
