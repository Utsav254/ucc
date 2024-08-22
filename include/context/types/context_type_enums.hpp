#pragma once
#include <string>

namespace context {

enum class type_primitive {
	INT,
	CHAR,
	LONG,
	SHORT,
	
	FLOAT,
	DOUBLE,
};

enum class type_qualifier {
	NONE = 0,
	CONST,
	VOLATILE,
	RESTRICT,
};

void type_primitive_get_str(const type_primitive tp , std::string& in);
void type_qualifier_get_str(const type_qualifier tq , std::string& in);

}
