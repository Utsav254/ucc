#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <stack>

class context;
class symbolinfo;

extern context *ctx;

class context {
public:
	context() {
		scopes_["global"] = "global";
		//add all standard types to the types_ table
		//set up all basic stuff
	}
	~context() = default;

	//temporary type set functions:
	void insert_custom_type_tmp(std::string type_name) {
		types_tmp_.insert(type_name);
	}
	bool is_member_types_tmp(std::string query) {
		return (types_tmp_.find(query) != types_tmp_.end());
	}
	void clear_type_tmp() {
		types_tmp_.clear();
		return;
	}


private:
	//holds temp types before assembling types into the type hierarchy table
	//should be cleared one no longer needed
	std::unordered_set<std::string>	types_tmp_;

	//used to keep track of current scope as tree is traversed
	//<current_scope_name>
	std::stack<std::string> traversed_scopes_;

	//holds the scope hierarchy of scopes
	// < scope_name , parent_scope >
	std::unordered_map<std::string , std::string> scopes_;

	//holds the type info with their scopes:
	// < scope_name , type_name >
	std::unordered_map<std::string , std::string> types_;

	//should later hold parameters and variables and all sorts of stuff
	//<scope_name , < symbol_identifier , symbol information > >
	std::unordered_map<std::string , std::unordered_map<std::string , symbolinfo*>> variables_;
	//...
};

#endif
