#ifndef CONTEXT_INTERNAL_HPP
#define CONTEXT_INTERNAL_HPP

#include <unordered_set>
#include <unordered_map>
#include <string>
#include <stack>

namespace context{
	namespace internal {
//----------------------------------------Temporary_Types_Handler(parse time) holds typedef--------------------------------------
		//holds temp types before assembling types into the type hierarchy table
		//should be cleared one no longer needed
		extern std::unordered_set<std::string>	types_tmp_;
//--------------------------------------------------Scopes handler and hierarchies-----------------------------------------------
		//used to keep track of current scope as tree is traversed
		//<current_scope_name>
		extern std::stack<std::string> traversed_scopes_;

		//holds the scope hierarchy of scopes
		// < scope_name , parent_scope >
		extern std::unordered_map<std::string , std::string> scopes_;

	}
}

#endif
