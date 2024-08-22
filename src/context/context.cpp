#include "context/context.hpp"
#include "context/context_internal.hpp"

void context::initialise() {
	internal::scopes_["global"] = "global";
}

void context::free() {

}



