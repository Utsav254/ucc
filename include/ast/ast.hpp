#ifndef AST_HPP
#define AST_HPP

#include "node.hpp"

//miscellanious stuff
#include "misc/primaries.hpp"
#include "misc/misc.hpp"
#include "misc/initialiser_designator.hpp"

//declaration stuff
#include "decls/casting.hpp"
#include "decls/specifier_qualifiers.hpp"
#include "decls/declarator.hpp"
#include "decls/declaration.hpp"
#include "decls/pointer.hpp"
#include "decls/type_name.hpp"
#include "decls/abstract_declarator.hpp"

//functions:
#include "functions/function_definition.hpp"
#include "functions/parameter.hpp"
#include "functions/function_declarator.hpp"
#include "functions/function_call.hpp"
#include "functions/function_pointer.hpp"
#include "functions/abstract_functions.hpp"

//arithmetic:
#include "arithmetic/incr_decr_op.hpp"
#include "arithmetic/rl_operators.hpp"
#include "arithmetic/assign_op.hpp"
#include "arithmetic/cond_expression.hpp"
#include "arithmetic/unary.hpp"

//array:
#include "arrays/array_definition.hpp"
#include "arrays/array_index.hpp"
#include "arrays/abstract_arrays.hpp"

//statements:
#include "statements/jumps.hpp"
#include "statements/block.hpp"
#include "statements/switch_case.hpp"
#include "statements/if_else.hpp"
#include "statements/while.hpp"
#include "statements/for.hpp"

//struct and unions:
#include "struct_union_enum/struct_union.hpp"
#include "struct_union_enum/struct_union_decls.hpp"
#include "struct_union_enum/struct_union_member.hpp"
#include "struct_union_enum/enum_spec.hpp"
#include "struct_union_enum/enumerator.hpp"


#endif

