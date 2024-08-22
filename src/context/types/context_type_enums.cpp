#include "context/types/context_type_enums.hpp"

using namespace context;

void type_primitive_get_str(const type_primitive tp , std::string& in) {
	switch(tp) {
		case type_primitive::INT :
			in = "int";
			break;
		case type_primitive::CHAR :
			in = "char";
			break;
		case type_primitive::LONG:
			in = "long";
			break;
		case type_primitive::SHORT:
			in = "short";
			break;
		case type_primitive::FLOAT:
			in = "float";
			break;
		case type_primitive::DOUBLE:
			in = "double";
			break;
		default:
			in = "unknown";
			break;
	}
}

void type_qualifier_get_str(const type_qualifier tq , std::string& in) {
	switch(tq) {
        case type_qualifier::NONE:
			in = "";
			break;
        case type_qualifier::CONST:
			in = "const";
			break;
        case type_qualifier::VOLATILE:
			in = "volatile";
			break;
        case type_qualifier::RESTRICT:
			in = "restrict";
			break;
		default:
			in = "unknown";
			break;
    }
}


