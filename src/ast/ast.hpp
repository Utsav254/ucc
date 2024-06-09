#ifndef AST_HPP
#define AST_HPP

#include "node.hpp"

//miscellanious stuff
#include "misc/primaries.hpp"
#include "misc/misc.hpp"

//declaration stuff
#include "decls/specifier_qualifiers.hpp"
#include "decls/declarator.hpp"
#include "decls/declaration.hpp"

//functions:
#include "functions/function_definition.hpp"
#include "functions/parameter.hpp"
#include "functions/function_declarator.hpp"
#include "functions/function_call.hpp"

//arithmetic:
#include "arithmetic/incr_decr_op.hpp"
#include "arithmetic/rl_operators.hpp"
#include "arithmetic/assign_op.hpp"
#include "arithmetic/cond_expression.hpp"

//array:
#include "arrays/array_definition.hpp"
#include "arrays/array_index.hpp"

//statements:
#include "statements/jumps.hpp"
#include "statements/block.hpp"
#include "statements/switch_case.hpp"
#include "statements/if_else.hpp"
#include "statements/while.hpp"
#include "statements/for.hpp"

//struct and unions:
#include "struct_union/struct_union.hpp"
#include "struct_union/struct_union_decls.hpp"
#include "struct_union/struct_union_member.hpp"


#endif

