#include "context/context_internal.hpp"

namespace context{
	namespace internal {
		std::unordered_set<std::string>	types_tmp_;
//-----------------------------------------------------------------------------------------------------------------------------
		std::stack<std::string> traversed_scopes_;

		std::unordered_map<std::string , std::string> scopes_;

	}
}
	
