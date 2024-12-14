%code requires{
	//from: https://www.quut.com/c/ANSI-C-grammar-y-1999.html
    #include "ast/ast.hpp"
	#include "error.hpp"
	#include <string>
	#include <iostream>
	#include <variant>

    extern std::unique_ptr<node> root_node;
    extern FILE *yyin;
	extern int yylineno;

    int yylex(void);
    void yyerror(const char *);

	#define YYLTYPE YYLTYPE
	#define YYLTYPE_IS_DECLARED 1 // Inform Bison that YYLTYPE is declared
	#include "ast/locations.hpp"
}

// Use std::variant for semantic values
%define api.value.type {
std::variant
<
    std::unique_ptr<node>, 
    std::unique_ptr<nodelist>, 
    char, 
    long, 
    double, 
    std::unique_ptr<std::string>, 
    yytokentype
>
}

// Specify custom location handling
%locations
%define api.location.type {YYLTYPE}

// Enable detailed error messages
%define parse.error detailed

%token IDENTIFIER INT_CONSTANT CHAR_CONSTANT FLOAT_CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME
%token TYPEDEF EXTERN STATIC AUTO REGISTER INLINE RESTRICT
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <Node> external_declaration function_definition primary_expression postfix_expression 
%type <Node> unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression
%type <Node> equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression 
%type <Node> conditional_expression assignment_expression constant_expression declaration logical_or_expression
%type <Node> init_declarator type_specifier struct_declaration 
%type <Node> struct_declarator enum_specifier enumerator declarator direct_declarator parameter_declaration
%type <Node> type_name abstract_declarator direct_abstract_declarator initializer statement labeled_statement
%type <Node> compound_statement expression_statement selection_statement iteration_statement jump_statement
%type <Node> storage_class_specifier block_item type_qualifier function_specifier struct_or_union_specifier struct_or_union
%type <Node> designation designator

%type <Nodes> declaration_list init_declarator_list translation_unit parameter_type_list parameter_list argument_expression_list 
%type <Nodes> block_item_list declaration_specifiers expression identifier_list struct_declaration_list specifier_qualifier_list 
%type <Nodes> initializer_list type_qualifier_list pointer enumerator_list struct_declarator_list designator_list

%type <number_int> INT_CONSTANT
%type <number_float> FLOAT_CONSTANT
%type <letter_char> CHAR_CONSTANT
%type <string> IDENTIFIER STRING_LITERAL TYPE_NAME

%left ','  // Comma operator
%left OR_OP
%left AND_OP
%left '|'
%left '^'
%left '&'
%left '<' '>' LE_OP GE_OP
%left EQ_OP NE_OP
%left '+' '-'
%left '*' '/' '%'
%left RIGHT_OP LEFT_OP
%right INC_OP DEC_OP
%right PTR_OP '.'
%right '=' MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN AND_ASSIGN OR_ASSIGN XOR_ASSIGN RIGHT_ASSIGN LEFT_ASSIGN
%right SIZEOF


%start ROOT

%%

primary_expression
	: IDENTIFIER
	{std::get<std::unique_ptr<node>>($$) = std::make_unique<identifier>(@$ , std::move($1));}
	| INT_CONSTANT
	{$$ = std::make_unique<int_constant>(@$ , std::move($1));}
	| FLOAT_CONSTANT
	{$$ = std::make_unique<float_constant>(@$ , std::move($1));}
	| CHAR_CONSTANT
	{$$ = std::make_unique<char_constant>(@$ , std::move($1));}
	| STRING_LITERAL
	{$$ = std::make_unique<string_literal>(@$ , std::move($1));}
	| '(' expression ')'
	{$$ = std::move($2);}
	;

postfix_expression
	: primary_expression
	{$$ = std::move($1);}
	| postfix_expression '[' expression ']'
	{$$ = std::make_unique<array_index>(@$ , std::move($1) , std::move($3));}
	| postfix_expression '(' ')'
	{$$ = std::make_unique<function_call>(@$ , std::move($1));}
	| postfix_expression '(' argument_expression_list ')'
	{$$ = std::make_unique<function_call_arg>(@$ , std::move($1) , std::move($3));}
	| postfix_expression '.' IDENTIFIER
	{$$ = std::make_unique<dot_member_op>(@$ , std::move($1) , std::make_unique<identifier>(@3 , std::move($3)));}
	| postfix_expression PTR_OP IDENTIFIER
	{$$ = std::make_unique<ptr_member_op>(@$ , std::move($1) , std::make_unique<identifier>(@3 , std::move($3)));}
	| postfix_expression INC_OP
	{$$ = std::make_unique<postfix_incr>(@$ , std::move($1));}
	| postfix_expression DEC_OP
	{$$ = std::make_unique<postfix_decr>(@$ , std::move($1));}
	| '(' type_name ')' '{' initializer_list '}'
	{$$ = std::make_unique<cast_compound_literal>(@$ , std::move($2) , std::move($5));}
	| '(' type_name ')' '{' initializer_list ',' '}'
	{$$ = std::make_unique<cast_compound_literal>(@$ , std::move($2) , std::move($5));}
	;

argument_expression_list
	: assignment_expression
	{$$ = std::make_unique<argument_expression_list>(@$ , std::move($1));}
	| argument_expression_list ',' assignment_expression
	{$1->pushback(std::move($3)); $$ = std::move($1);}
	

unary_expression
	: postfix_expression
	{$$ = std::move($1);}
	| INC_OP unary_expression
	{$$ = std::make_unique<unary_incr>(@$ , std::move($2));}
	| DEC_OP unary_expression
	{$$ = std::make_unique<unary_decr>(@$ , std::move($2));}
	| SIZEOF unary_expression
	{$$ = std::make_unique<sizeof_node>(@$ , std::move($2));}
	| SIZEOF '(' type_name ')'
	{$$ = std::make_unique<sizeof_node_type>(@$ , std::move($3));}
	| '&' cast_expression
	{$$ = std::make_unique<unary_addressof>(@$ , std::move($2));}
	| '*' cast_expression
	{$$ = std::make_unique<unary_pointer_deref>(@$ , std::move($2));}
	| '+' cast_expression
	{$$ = std::make_unique<unary_positive>(@$ , std::move($2));}
	| '-' cast_expression
	{$$ = std::make_unique<unary_negative>(@$ , std::move($2));}
	| '~' cast_expression
	{$$ = std::make_unique<unary_bitwise_not>(@$ , std::move($2));}
	| '!' cast_expression
	{$$ = std::make_unique<unary_logical_not>(@$ , std::move($2));}
	;

cast_expression
	: unary_expression
	{$$ = std::move($1);}
	| '(' type_name ')' cast_expression
	{$$ = std::make_unique<cast_expression>(@$ , std::move($2) , std::move($4));}
	;

multiplicative_expression
	: cast_expression
	{$$ = std::move($1);}
	| multiplicative_expression '*' cast_expression
	{$$ = std::make_unique<mul>(@$ , std::move($1), std::move($3));}
	| multiplicative_expression '/' cast_expression
	{$$ = std::make_unique<divi>(@$ , std::move($1), std::move($3));}
	| multiplicative_expression '%' cast_expression
	{$$ = std::make_unique<modulo>(@$ , std::move($1), std::move($3));}
	;

additive_expression
	: multiplicative_expression
	{$$ = std::move($1);}
	| additive_expression '+' multiplicative_expression
	{$$ = std::make_unique<add>(@$ , std::move($1), std::move($3));}
	| additive_expression '-' multiplicative_expression
	{$$ = std::make_unique<sub>(@$ , std::move($1), std::move($3));}
	;

shift_expression
	: additive_expression
	{$$ = std::move($1);}
	| shift_expression LEFT_OP additive_expression
	{$$ = std::make_unique<left_shift>(@$ , std::move($1), std::move($3));}
	| shift_expression RIGHT_OP additive_expression
	{$$ = std::make_unique<right_shift>(@$ , std::move($1), std::move($3));}
	;

relational_expression
	: shift_expression
	{$$ = std::move($1);}
	| relational_expression '<' shift_expression
	{$$ = std::make_unique<less_than>(@$ , std::move($1), std::move($3));}
	| relational_expression '>' shift_expression
	{$$ = std::make_unique<greater_than>(@$ , std::move($1), std::move($3));}
	| relational_expression LE_OP shift_expression
	{$$ = std::make_unique<less_eq_than>(@$ , std::move($1), std::move($3));}
	| relational_expression GE_OP shift_expression
	{$$ = std::make_unique<greater_eq_than>(@$ , std::move($1), std::move($3));}
	;

equality_expression
	: relational_expression
	{$$ = std::move($1);}
	| equality_expression EQ_OP relational_expression
	{$$ = std::make_unique<equality>(@$ , std::move($1), std::move($3));}
	| equality_expression NE_OP relational_expression
	{$$ = std::make_unique<not_equal>(@$ , std::move($1), std::move($3));}
	;

and_expression
	: equality_expression
	{$$ = std::move($1);}
	| and_expression '&' equality_expression
	{$$ = std::make_unique<andop>(@$ , std::move($1), std::move($3));}
	;

exclusive_or_expression
	: and_expression
	{$$ = std::move($1);}
	| exclusive_or_expression '^' and_expression
	{$$ = std::make_unique<xorop>(@$ , std::move($1), std::move($3));}
	;

inclusive_or_expression
	: exclusive_or_expression
	{$$ = std::move($1);}
	| inclusive_or_expression '|' exclusive_or_expression
	{$$ = std::make_unique<orop>(@$ , std::move($1), std::move($3));}
	;

logical_and_expression
	: inclusive_or_expression
	{$$ = std::move($1);}
	| logical_and_expression AND_OP inclusive_or_expression
	{$$ = std::make_unique<log_andop>(@$ , std::move($1), std::move($3));}
	;

logical_or_expression
	: logical_and_expression
	{$$ = std::move($1);}
	| logical_or_expression OR_OP logical_and_expression
	{$$ = std::make_unique<log_orop>(@$ , std::move($1), std::move($3));}
	;

conditional_expression
	: logical_or_expression
	{$$ = std::move($1);}
	| logical_or_expression '?' expression ':' conditional_expression
	{$$ = std::make_unique<conditional_expression>(@$, std::move($1), std::move($3), std::move($5));}
	;

assignment_expression
	: conditional_expression
	{$$ = std::move($1);}
	| unary_expression '=' assignment_expression
	{$$ = std::make_unique<equals_assn>(@$ , std::move($1) , std::move($3));}
	| unary_expression MUL_ASSIGN assignment_expression
	{$$ = std::make_unique<mul_assn>(@$ , std::move($1) , std::move($3));}
	| unary_expression DIV_ASSIGN assignment_expression
	{$$ = std::make_unique<div_assn>(@$ , std::move($1) , std::move($3));}
	| unary_expression MOD_ASSIGN assignment_expression
	{$$ = std::make_unique<modu_assn>(@$ , std::move($1) , std::move($3));}
	| unary_expression ADD_ASSIGN assignment_expression
	{$$ = std::make_unique<add_assn>(@$ , std::move($1) , std::move($3));}
	| unary_expression SUB_ASSIGN assignment_expression
	{$$ = std::make_unique<sub_assn>(@$ , std::move($1) , std::move($3));}
	| unary_expression LEFT_ASSIGN assignment_expression
	{$$ = std::make_unique<left_assn>(@$ , std::move($1) , std::move($3));}
	| unary_expression RIGHT_ASSIGN assignment_expression
	{$$ = std::make_unique<right_assn>(@$ , std::move($1) , std::move($3));}
	| unary_expression AND_ASSIGN assignment_expression
	{$$ = std::make_unique<and_assn>(@$ , std::move($1) , std::move($3));}
	| unary_expression XOR_ASSIGN assignment_expression
	{$$ = std::make_unique<xor_assn>(@$ , std::move($1) , std::move($3));}
	| unary_expression OR_ASSIGN assignment_expression
	{$$ = std::make_unique<or_assn>(@$ , std::move($1) , std::move($3));}
	;

expression
	: assignment_expression
	{$$ = std::make_unique<expression_list>(@$ , std::move($1));}
	| expression ',' assignment_expression
	{$1->pushback(std::move($3)); $$ = std::move($1);}
	;

constant_expression
	: conditional_expression
	{$$ = std::move($1);}
	;

declaration
	: declaration_specifiers ';'
	{$$ = std::make_unique<declaration>(@$ , std::move($1));}
	| declaration_specifiers init_declarator_list ';'
	{$$ = std::make_unique<declaration_init_decl>(@$ , std::move($1) , std::move($2));}
	;

declaration_specifiers
	: storage_class_specifier
	{$$ = std::make_unique<declaration_specifiers>(@$ , std::move($1));}
	| storage_class_specifier declaration_specifiers
	{$2->pushback(std::move($1)); $$ = std::move($2);}
	| type_specifier
	{$$ = std::make_unique<declaration_specifiers>(@$ , std::move($1));}
	| type_specifier declaration_specifiers
	{$2->pushback(std::move($1)); $$ = std::move($2);}
	| type_qualifier
	{$$ = std::make_unique<declaration_specifiers>(@$ , std::move($1));}
	| type_qualifier declaration_specifiers
	{$2->pushback(std::move($1)); $$ = std::move($2);}
	| function_specifier
	{$$ = std::make_unique<declaration_specifiers>(@$ , std::move($1));}
	| function_specifier declaration_specifiers
	{$2->pushback(std::move($1)); $$ = std::move($2);}
	;

init_declarator_list
	: init_declarator
	{$$ = std::make_unique<init_declaration_list>(@$ , std::move($1));}
	| init_declarator_list ',' init_declarator
	{$1->pushback(std::move($3)); $$ = std::move($1);}
	;

init_declarator
	: declarator
	{$$ = std::make_unique<init_declarator>(@$ , std::move($1));}
	| declarator '=' initializer
	{$$ = std::make_unique<init_declarator_ini>(@$ , std::move($1) , std::move($3));}
	;

storage_class_specifier
	: TYPEDEF
	{$$ = std::make_unique<storage_class_specifier>(@$ , "TYPEDEF");}
	| EXTERN
	{$$ = std::make_unique<storage_class_specifier>(@$ , "EXTERN");}
	| STATIC
	{$$ = std::make_unique<storage_class_specifier>(@$ , "STATIC");}
	| AUTO
	{$$ = std::make_unique<storage_class_specifier>(@$ , "AUTO");}
	| REGISTER
	{$$ = std::make_unique<storage_class_specifier>(@$ , "REGISTER");}
	;

type_specifier
	: VOID
	{$$ = std::make_unique<type_specifier>(@$ , "VOID");}
	| CHAR
	{$$ = std::make_unique<type_specifier>(@$ , "CHAR");}
	| SHORT
	{$$ = std::make_unique<type_specifier>(@$ , "SHORT");}
	| INT
	{$$ = std::make_unique<type_specifier>(@$ , "INT");}
	| LONG
	{$$ = std::make_unique<type_specifier>(@$ , "LONG");}
	| FLOAT
	{$$ = std::make_unique<type_specifier>(@$ , "FLOAT");}
	| DOUBLE
	{$$ = std::make_unique<type_specifier>(@$ , "DOUBLE");}
	| SIGNED
	{$$ = std::make_unique<type_specifier>(@$ , "SIGNED");}
	| UNSIGNED
	{$$ = std::make_unique<type_specifier>(@$ , "UNSIGNED");}
	| struct_or_union_specifier
	{$$ = std::move($1);}
	| enum_specifier
	{$$ = std::move($1);}
	| TYPE_NAME
	{$$ = std::make_unique<type_specifier>(@$ , *$1); }
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}' 
	{$$ = std::make_unique<struct_union_spec_id_decl>(@$, std::move($1), std::make_unique<identifier>(@$, std::move($2)),
		std::move($4));}

	| struct_or_union '{' struct_declaration_list '}'
	{$$ = std::make_unique<struct_union_spec_decl>(@$ , std::move($1) , std::move($3));}
	| struct_or_union IDENTIFIER
	{$$ = std::make_unique<struct_union_spec_id>(@$, std::move($1), std::make_unique<identifier>(@$, std::move($2)));}
	;

struct_or_union
	: STRUCT
	{$$ = std::make_unique<struct_union>(@$ , "struct");}
	| UNION
	{$$ = std::make_unique<struct_union>(@$ , "union");}
	;

struct_declaration_list
	: struct_declaration
	{$$ = std::make_unique<struct_declaration_list>(@$ , std::move($1));}
	| struct_declaration_list struct_declaration
	{$1->pushback(std::move($2)); $$ = std::move($1);}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	{$$ = std::make_unique<struct_declaration>(@$ , std::move($1) , std::move($2));}
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	{$2->pushback(std::move($1)); $$ = std::move($2);}
	| type_specifier
	{$$ = std::make_unique<specifier_qualifier_list>(@$ , std::move($1));}
	| type_qualifier specifier_qualifier_list
	{$2->pushback(std::move($1)); $$ = std::move($2);}
	| type_qualifier
	{$$ = std::make_unique<specifier_qualifier_list>(@$ , std::move($1));}
	;

struct_declarator_list
	: struct_declarator
	{$$ = std::make_unique<struct_declarator_list>(@$ , std::move($1));}
	| struct_declarator_list ',' struct_declarator
	{$1->pushback(std::move($3)); $$ = std::move($1);}
	;

struct_declarator
	: declarator
	{$$ = std::make_unique<struct_declarator>(@$ , std::move($1));}
	| ':' constant_expression
	{$$ = std::make_unique<struct_declarator_padding>(@$ , std::move($2));}
	| declarator ':' constant_expression
	{$$ = std::make_unique<struct_declarator_size>(@$ , std::move($1) , std::move($3));}
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	{$$ = std::make_unique<enum_spec>(@$ , std::move($3));}
	| ENUM IDENTIFIER '{' enumerator_list '}'
	{$$ = std::make_unique<enum_spec_id>(@$ , std::make_unique<identifier>(@2 , std::move($2)) , std::move($4));}
	| ENUM '{' enumerator_list ',' '}'
	{$$ = std::make_unique<enum_spec>(@$ , std::move($3));}
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'
	{$$ = std::make_unique<enum_spec_id>(@$ , std::make_unique<identifier>(@2 , std::move($2)) , std::move($4));}
	| ENUM IDENTIFIER
	{$$ = std::make_unique<enum_declaration>(@$ , std::make_unique<identifier>(@2 , std::move($2)));}
	;

enumerator_list
	: enumerator
	{$$ = std::make_unique<enumerator_list>(@$ , std::move($1));}
	| enumerator_list ',' enumerator
	{$1->pushback(std::move($3)); $$ = std::move($1);}
	;

enumerator
	: IDENTIFIER
	{$$ = std::make_unique<enumerator>(@$, std::make_unique<identifier>(@1, std::move($1)) );}
	| IDENTIFIER '=' constant_expression
	{$$ = std::make_unique<enumerator_const_expr>(@1, std::make_unique<identifier>(@1, std::move($1)), std::move($3));}
	;

type_qualifier
	: CONST
	{$$ = std::make_unique<type_qualifier>(@$ , "CONST");}
	| RESTRICT
	{$$ = std::make_unique<type_qualifier>(@$ , "RESTRICT");}
	| VOLATILE
	{$$ = std::make_unique<type_qualifier>(@$ , "VOLATILE");}
	;

function_specifier
	: INLINE
	{$$ = std::make_unique<function_specifier>(@$ , "INLINE");}
	;

declarator
	: pointer direct_declarator
	{$$ = std::make_unique<declarator_pointer>(@$ , std::move($1), std::move($2));}
	| direct_declarator
	{$$ = std::make_unique<declarator>(@$ , std::move($1));}
	;

direct_declarator
	: IDENTIFIER
	{$$ = std::make_unique<identifier>(@$ , std::move($1));}
	| direct_declarator '[' assignment_expression ']'
	{$$ = std::make_unique<array_definition_size>(@$ , std::move($1) , std::move($3));}
	| direct_declarator '[' ']'
	{$$ = std::make_unique<array_definition>(@$ , std::move($1));}
	| direct_declarator '(' ')'
	{$$ = std::make_unique<function_declarator>(@$ , std::move($1));}
	| direct_declarator '(' parameter_type_list ')'
	{$$ = std::make_unique<function_declarator_param>(@$ , std::move($1) , std::move($3));}
	| direct_declarator '(' identifier_list ')'
	{$$ = std::make_unique<function_declarator_id_list>(@$ , std::move($1) , std::move($3));}
	| '(' declarator ')'
	{$$ = std::move($2);}
	| direct_declarator '[' type_qualifier_list assignment_expression ']'
	{$$ = std::make_unique<array_definition_type_qual_size>(@$ , std::move($1) , std::move($3) , std::move($4));}
	| direct_declarator '[' type_qualifier_list ']'
	{$$ = std::make_unique<array_definition_type_qual>(@$ , std::move($1) , std::move($3));}
	;

pointer
	: '*'
	{$$ = std::make_unique<pointer_list>(@$ , std::make_unique<pointer>(@$) );}
	| '*' pointer
	{$2->pushback( std::make_unique<pointer>(@1) ); $$ = std::move($2);}
	| '*' type_qualifier_list
	{$$ = std::make_unique<pointer_list>(@$ , std::make_unique<pointer>(@1)); $$->pushback(std::move($2));}
	| '*' type_qualifier_list pointer
	{$$ = std::make_unique<pointer_list>(@$ , std::make_unique<pointer>(@1)); $$->pushback(std::move($2)); 
		$$->pushback(std::move($3));}
	;

type_qualifier_list
	: type_qualifier
	{$$ = std::make_unique<type_qualifier_list>(@$ , std::move($1));}
	| type_qualifier_list type_qualifier
	{$1->pushback(std::move($2));  $$ = std::move($1);}
	;


parameter_type_list
	: parameter_list
	{$$ = std::move($1);}
	| parameter_list ',' ELLIPSIS
	{$1->pushback(std::make_unique<ellipsis>(@$)); $$ = std::move($1);}
	;

parameter_list
	: parameter_declaration
	{$$ = std::make_unique<parameter_list>(@$ , std::move($1));}
	| parameter_list ',' parameter_declaration
	{$1->pushback(std::move($3)); $$ = std::move($1);}
	;

parameter_declaration
	: declaration_specifiers declarator
	{$$ = std::make_unique<parameter_full_decl>(@$ , std::move($1) , std::move($2));}
	| declaration_specifiers
	{$$ = std::make_unique<parameter_decl>(@$ , std::move($1)); /*used if only the function trace needs to be given*/}
	| declaration_specifiers abstract_declarator
	{$$ = std::make_unique<parameter_decl_abstract>(@$ , std::move($1) , std::move($2));}
	;

identifier_list
	: IDENTIFIER
	{$$ = std::make_unique<identifier_list>(@$ , std::make_unique<identifier>(@$ , std::move($1)));}
	| identifier_list ',' IDENTIFIER
	{$1->pushback(std::make_unique<identifier>(@$ , std::move($3))); $$ = std::move($1);}
	;

type_name
	: specifier_qualifier_list
	{$$ = std::make_unique<type_name>(@$ , std::move($1));}
	| specifier_qualifier_list abstract_declarator
	{$$ = std::make_unique<type_name_abstract>(@$ , std::move($1) , std::move($2));}
	;

abstract_declarator
	: pointer
	{$$ = std::move($1);}
	| direct_abstract_declarator
	{$$ = std::make_unique<abstract_declarator>(@$ , std::move($1));}
	| pointer direct_abstract_declarator
	{$$ = std::make_unique<abstract_declarator_pointer>(@$ , std::move($1) , std::move($2));}
	;

direct_abstract_declarator
	: '[' ']'
	{$$ = std::make_unique<unamed_empty_array>(@$);}
	| '[' assignment_expression ']'
	{$$ = std::make_unique<unamed_empty_array_size>(@$ , std::move($2));}
	| direct_abstract_declarator '[' ']'
	{$$ = std::make_unique<array_decl_abstract>(@$ , std::move($1));}
	| direct_abstract_declarator '[' assignment_expression ']'
	{$$ = std::make_unique<array_decl_abstract_size>(@$ , std::move($1) , std::move($3));}
	| '(' ')'
	{$$ = std::make_unique<unamed_empty_declaration>(@$);}
	| '(' parameter_type_list ')'
	{$$ = std::make_unique<unamed_abstract_function_parameters>(@$ , std::move($2));}
	| direct_abstract_declarator '(' ')'
	{$$ = std::make_unique<abstract_function>(@$ , std::move($1));}
	| direct_abstract_declarator '(' parameter_type_list ')'
	{$$ = std::make_unique<abstract_function_parameters>(@$ , std::move($1) , std::move($3));}
	| '(' abstract_declarator ')'
	{$$ = std::move($2);}
	;

initializer
	: assignment_expression
	{$$ = std::move($1);}
	| '{' initializer_list '}'
	{$$ = std::make_unique<initialiser>(@$ , std::move($2));}
	| '{' initializer_list ',' '}'
	{$$ = std::make_unique<initialiser>(@$ , std::move($2));}
	;

initializer_list
	: initializer
	{$$ = std::make_unique<initialiser_list>(@$ , std::move($1));}
	| designation
	{$$ = std::make_unique<initialiser_list>(@$ , std::move($1));}
	| initializer_list ',' initializer
	{$1->pushback(std::move($3)); $$ = std::move($1);}
	| initializer_list ',' designation
	{$1->pushback(std::move($3)); $$ = std::move($1);}
	;

designation
	: designator_list '=' initializer
	{$$ = std::make_unique<designation>(@$ , std::move($1) , std::move($3));}

designator_list
	: designator
	{$$ = std::make_unique<designator_list>(@$ , std::move($1));}
	| designator_list designator
	{$1->pushback(std::move($2)); $$ = std::move($1);}
	;

designator
	: '[' constant_expression ']'
	{$$ = std::make_unique<designator_constant_expr>(@$ , std::move($2));}
	| '.' IDENTIFIER
	{$$ = std::make_unique<designator_identifier>(@$ , std::make_unique<identifier>(@2 , std::move($2)));}
	;

statement
	: labeled_statement
	{$$ = std::move($1);}
	| compound_statement
	{$$ = std::move($1);}
	| expression_statement
	{$$ = std::move($1);}
	| selection_statement
	{$$ = std::move($1);}
	| iteration_statement
	{$$ = std::move($1);}
	| jump_statement
	{$$ = std::move($1);}
	;

labeled_statement
	: IDENTIFIER ':' statement
	{$$ = std::make_unique<goto_target>(@$ , std::make_unique<identifier>(@$ , std::move($1)) , std::move($3));}
	| CASE constant_expression ':' statement
	{$$ = std::make_unique<case_node>(@$ , std::move($2) , std::move($4));}
	| DEFAULT ':' statement
	{$$ = std::make_unique<case_default_node>(@$ , std::move($3));}
	;

compound_statement
	: '{' '}'
	{$$ = std::make_unique<empty>(@$);}
	| '{' block_item_list '}'
	{$$ = std::move($2);}
	;

block_item_list
	: block_item
	{$$ = std::make_unique<block_item_list>(@$ , std::move($1));}
	| block_item_list block_item
	{$1->pushback(std::move($2)) ; $$ = std::move($1);}
	;

block_item
	: declaration
	{$$ = std::move($1);}
	| statement
	{$$ = std::move($1);}
	;

expression_statement
	: ';'
	{$$ = std::make_unique<empty>(@$);}
	| expression ';'
	{$$ = std::move($1);}
	;

selection_statement
	: IF '(' expression ')' statement
	{$$ = std::make_unique<if_node>(@$ , std::move($3) , std::move($5));}
	| IF '(' expression ')' statement ELSE statement
	{$$ = std::make_unique<if_else_node>(@$ , std::move($3) , std::move($5) , std::move($7));}
	| SWITCH '(' expression ')' statement 
	{$$ = std::make_unique<switch_node>(@$ , std::move($3) , std::move($5));}
	;

iteration_statement
	: WHILE '(' expression ')' statement
	{$$ = std::make_unique<while_node>(@$ , std::move($3) , std::move($5));}
	| DO statement WHILE '(' expression ')' ';'
	{$$ = std::make_unique<do_while_node>(@$ , std::move($2) , std::move($5));}
	| FOR '(' expression_statement expression_statement ')' statement
	{$$ = std::make_unique<for_node_ext>(@$ , std::move($3) , std::move($4) , std::move($6));}
	| FOR '(' expression_statement expression_statement expression ')' statement
	{$$ = std::make_unique<for_node_ext_mod>(@$ , std::move($3) , std::move($4) , std::move($5) , std::move($7));}
	| FOR '(' declaration expression_statement ')' statement
	{$$ = std::make_unique<for_node>(@$ , std::move($3) , std::move($4) , std::move($6));}
	| FOR '(' declaration expression_statement expression ')' statement
	{$$ = std::make_unique<for_node_mod>(@$ , std::move($3) , std::move($4) , std::move($5) , std::move($7));}
	;

jump_statement
	: GOTO IDENTIFIER ';' 
	{$$ = std::make_unique<jump_statement_goto>(@$ , std::make_unique<identifier>(@$ , std::move($2)));}
	| CONTINUE ';' 
	{$$ = std::make_unique<jump_statement_continue>(@$);}
	| BREAK ';' 
	{$$ = std::make_unique<jump_statement_break>(@$);}
	| RETURN ';' 
	{$$ = std::make_unique<jump_statement_ret>(@$);}
	| RETURN expression ';' 
	{$$ = std::make_unique<jump_statement_ret_expr>(@$ , std::move($2));}
	;

ROOT
	:translation_unit
	{root_node = std::move($1);}

translation_unit
	: external_declaration
	{$$ = std::make_unique<translation_unit>(@$ , std::move($1));}
	| translation_unit external_declaration
	{$1->pushback(std::move($2)); $$ = std::move($1);}
	;

external_declaration
	: function_definition
	{$$ = std::move($1);}
	| declaration
	{$$ = std::move($1);}
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement 
	{$$ = std::make_unique<function_definition_decl_list>(@$, std::move($1), std::move($2), std::move($3), std::move($4));}
	| declaration_specifiers declarator compound_statement 
	{$$ = std::make_unique<function_definition>(@$, std::move($1), std::move($2), std::move($3));}
	;

declaration_list
	: declaration
	{$$ = std::make_unique<declaration_list>(@$ , std::move($1));}
	| declaration_list declaration 
	{$1->pushback(std::move($2)); $$ = std::move($1);}
	;


%%

void yyerror(char const *s) {
	std::cout << "got error at line: " << yylloc.first_line << ":" << yylloc.first_column << std::endl;
	errors::add_err(new error(yylloc , s , false)); 
	errors::die(s);
}


std::unique_ptr<node> parseAST(std::string file_name) {

	yyin = fopen(file_name.c_str(), "r");

	if(yyin == NULL){
		errors::die("Failure in opening source file");
	}

	root_node = nullptr;
	yyparse();
	return std::move(root_node);
}


