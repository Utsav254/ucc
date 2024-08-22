#include "context/context_type_tmp.hpp"
#include "context/context_internal.hpp"

void context::insert_custom_type_tmp(const std::string& type_name) {
	internal::types_tmp_.insert(type_name);
}

bool context::is_member_types_tmp(const std::string& query) {
	return (internal::types_tmp_.find(query) != internal::types_tmp_.end());
}

void context::clear_type_tmp() {
	internal::types_tmp_.clear();
	return;
}
