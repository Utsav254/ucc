#ifndef CONTEXT_TYPE_TMP_HPP
#define CONTEXT_TYPE_TMP_HPP

#include <string>

namespace context{
	
	//temporary type set functions:
	void insert_custom_type_tmp(const std::string& type_name);
	bool is_member_types_tmp(const std::string& query);
	void clear_type_tmp();

}

#endif
