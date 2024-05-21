#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <string>

class node {
public:

	node(){};
	virtual ~node(){};

	virtual void generateIR() const = 0;
	virtual void printAST(int depth) const = 0;

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
	//constructor
	nodelist(node *first_node) : nodes_({first_node}) {}
	//destrcutor
	~nodelist() {
		for(int i = 0 ; i < (int)nodes_.size() ; i++) {
			delete nodes_[i];
		}
	}

	//remaning override member functions
	void generateIR() const override;
	void printAST(int depth) const override;

	//derrived specific function:
	void pushback(node *next);


private:
	std::vector <node*> nodes_;
};





//parsing function to be defined the parser.y file
extern node *parseAST(std::string sourcepath);

//global root node of ast:
extern node *root_node;

#endif
