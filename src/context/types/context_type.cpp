#include "context/types/context_type.hpp"

void context::primitive_type::get_name(std::string& in) const {
	std::string tq;
	std::string tp;
	type_qualifier_get_str(tq_ , tq);
	type_primitive_get_str(tp_ , tp);
	in = tq + tp;
	return;
}

	
unsigned long context::primitive_type::get_sizeof() const {
	switch(tp_) {
        case type_primitive::INT:
			return sizeof(int);
        case type_primitive::CHAR:
			return sizeof(char);
        case type_primitive::LONG:
			return sizeof(long);
        case type_primitive::SHORT:
			return sizeof(short);
        case type_primitive::FLOAT:
			return sizeof(float);
        case type_primitive::DOUBLE:
			return sizeof(double);
    }
}

unsigned long context::primitive_type::get_alignof() const {
	switch(tp_) {
        case type_primitive::INT:
			return sizeof(int);
        case type_primitive::CHAR:
			return sizeof(char);
        case type_primitive::LONG:
			return sizeof(long);
        case type_primitive::SHORT:
			return sizeof(short);
        case type_primitive::FLOAT:
			return sizeof(float);
        case type_primitive::DOUBLE:
			return sizeof(double);
    }
}


void context::pointer_type::get_name(std::string& in) const {
	std::string pointer_to;
	std::string tq;
	pointer_to_->get_name(pointer_to);
	type_qualifier_get_str(tq_ , tq);

	in = pointer_to + "*" + tq;
	return;
}

	
unsigned long context::pointer_type::get_sizeof() const {
	return sizeof(void *);
}

unsigned long context::pointer_type::get_alignof() const {
	return sizeof(void *);
}

