#include "context.hpp"
#include <unordered_set>
#include <unordered_map>
#include <stack>

namespace context{
	namespace {
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
	}
	//basic functions:
	void initialise() {
		scopes_["global"] = "global";
	}
	
	void free() {
		for(auto& pair : variables_) {
			for(auto& inner_pair : pair.second) {
				if(inner_pair.second != nullptr) delete inner_pair.second;
			}
		}
		variables_.clear();
	}

	//typedef_temp functions
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

}



