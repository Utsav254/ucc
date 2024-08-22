#ifndef CONTEXT_TYPE_HPP
#define CONTEXT_TYPE_HPP

#include "context_type_enums.hpp"

namespace context {
class type {
public:
	type(const type_qualifier tq) : tq_(tq) {}
	virtual ~type() = default;
	virtual void get_name(std::string& in) const = 0;
	virtual unsigned long get_sizeof() const = 0;
	virtual unsigned long get_alignof() const = 0;

protected:
	const type_qualifier tq_;

	//needs to be a list ... a maximum of two type qualifiers ...
};
	
class primitive_type : public type {
public:
	primitive_type(const type_qualifier tq , const type_primitive tp) : type(tq) , tp_(tp) {}

	~primitive_type() = default;

	void get_name(std::string& in) const override;
	
	unsigned long get_sizeof() const override;

	unsigned long get_alignof() const override;

private:
	const type_primitive tp_;	
};

class pointer_type : public type {
public:
	pointer_type(const type_qualifier tq , const type* pointer_to) : type(tq) , pointer_to_(pointer_to) {}
	~pointer_type() {
		if(pointer_to_ != nullptr) delete pointer_to_;
	}

	void get_name(std::string& in) const override;
	
	unsigned long get_sizeof() const override;

	unsigned long get_alignof() const override;

private:
	const type *pointer_to_;
};

}

#endif
