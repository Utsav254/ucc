#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <string>

struct symbolinfo {
	std::string type_name;
	bool is_pointer;
	int pointer_depth;

	symbolinfo(std::string type , bool is_ptr , int ptr_depth) : 
		type_name(type) , is_pointer(is_ptr) , pointer_depth(ptr_depth){}

	symbolinfo(std::string type , bool is_ptr) : 
		type_name(type) , is_pointer(is_ptr) {
		if(is_pointer) pointer_depth = 1;
		else pointer_depth = 0;
	}

	//size
	//arr_size
	//stack location?
};

namespace context{
	void initialise();
	void free();
	
	//temporary type set functions:
	void insert_custom_type_tmp(std::string type_name);
	bool is_member_types_tmp(std::string query);
	void clear_type_tmp();


}

#endif
