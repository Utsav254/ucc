%code requires{
	//from: https://www.quut.com/c/ANSI-C-grammar-y-1999.html
    #include "ast/ast.hpp"
	#include "error.hpp"
	#include <string>
	#include <iostream>

    extern node *root_node;
    extern FILE *yyin;
	extern int yylineno;

    int yylex(void);
    void yyerror(const char *);

	#define YYLTYPE YYLTYPE
	#define YYLTYPE_IS_DECLARED 1 // Inform Bison that YYLTYPE is declared
	#include "ast/locations.hpp"
}

%union{
  node         *Node;
  nodelist     *Nodes;
  char         letter_char;	
  long         number_int;
  double       number_float;
  std::string  *string;
  yytokentype  token;
}

%locations
%define api.location.type {YYLTYPE}

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
	: IDENTIFIER { $$ = new identifier(@$ , *$1); delete $1; }
	| INT_CONSTANT { $$ = new int_constant(@$ , $1); }
	| FLOAT_CONSTANT { $$ = new float_constant(@$ , $1); }
	| CHAR_CONSTANT { $$ = new char_constant(@$ , $1); }
	| STRING_LITERAL { $$ = new string_literal(@$ , *$1); delete $1;}
	| '(' expression ')' {$$ = $2;}
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression '[' expression ']' { $$ = new array_index(@$ , $1 , $3); }
	| postfix_expression '(' ')' { $$ = new function_call(@$ , $1); }
	| postfix_expression '(' argument_expression_list ')' { $$ = new function_call_arg(@$ , $1 , $3); }
	| postfix_expression '.' IDENTIFIER { $$ = new dot_member_op(@$ , $1 , new identifier(@3 , *$3)); delete $3; }
	| postfix_expression PTR_OP IDENTIFIER {$$ = new ptr_member_op(@$ , $1 , new identifier(@3 , *$3)); delete $3; }
	| postfix_expression INC_OP { $$ = new postfix_incr(@$ , $1); }
	| postfix_expression DEC_OP { $$ = new postfix_decr(@$ , $1); }
	| '(' type_name ')' '{' initializer_list '}' { $$ = new cast_compound_literal(@$ , $2 , $5); }
	| '(' type_name ')' '{' initializer_list ',' '}' { $$ = new cast_compound_literal(@$ , $2 , $5); }
	;

argument_expression_list
	: assignment_expression { $$ = new argument_expression_list(@$ , $1); }
	| argument_expression_list ',' assignment_expression { $1->pushback($3); $$ = $1; }
	

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression { $$ = new unary_incr(@$ , $2); }
	| DEC_OP unary_expression { $$ = new unary_decr(@$ , $2); }
	| SIZEOF unary_expression { $$ = new sizeof_node(@$ , $2); }
	| SIZEOF '(' type_name ')' { $$ = new sizeof_node_type(@$ , $3); }
	| '&' cast_expression { $$ = new unary_addressof(@$ , $2); }
	| '*' cast_expression { $$ = new unary_pointer_deref(@$ , $2); }
	| '+' cast_expression { $$ = new unary_positive(@$ , $2); }
	| '-' cast_expression { $$ = new unary_negative(@$ , $2); }
	| '~' cast_expression { $$ = new unary_bitwise_not(@$ , $2); }
	| '!' cast_expression { $$ = new unary_logical_not(@$ , $2); }
	;

cast_expression
	: unary_expression { $$ = $1; }
	| '(' type_name ')' cast_expression { $$ = new cast_expression(@$ , $2 , $4); }
	;

multiplicative_expression
	: cast_expression { $$ = $1; }
	| multiplicative_expression '*' cast_expression {$$ = new mul(@$ , $1,$3);}
	| multiplicative_expression '/' cast_expression {$$ = new divi(@$ , $1,$3);}
	| multiplicative_expression '%' cast_expression {$$ = new modulo(@$ , $1,$3);}
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression {$$ = new add(@$ , $1,$3);}
	| additive_expression '-' multiplicative_expression {$$ = new sub(@$ , $1,$3);}
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression {$$ = new left_shift(@$ , $1,$3);}
	| shift_expression RIGHT_OP additive_expression {$$ = new right_shift(@$ , $1,$3);}
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression {$$ = new less_than(@$ , $1,$3);}
	| relational_expression '>' shift_expression {$$ = new greater_than(@$ , $1,$3);}
	| relational_expression LE_OP shift_expression {$$ = new less_eq_than(@$ , $1,$3);}
	| relational_expression GE_OP shift_expression {$$ = new greater_eq_than(@$ , $1,$3);}
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQ_OP relational_expression {$$ = new equality(@$ , $1,$3);}
	| equality_expression NE_OP relational_expression {$$ = new not_equal(@$ , $1,$3);}
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression '&' equality_expression {$$ = new andop(@$ , $1,$3);}
	;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression '^' and_expression {$$ = new xorop(@$ , $1,$3);}
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression {$$ = new orop(@$ , $1,$3);}
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression {$$ = new log_andop(@$ , $1,$3);}
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression {$$ = new log_orop(@$ , $1,$3);}
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression { $$ = new conditional_expression(@$ , $1 , $3 , $5); }
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression '=' assignment_expression { $$ = new equals_assn(@$ , $1 , $3); }
	| unary_expression MUL_ASSIGN assignment_expression { $$ = new mul_assn(@$ , $1 , $3); }
	| unary_expression DIV_ASSIGN assignment_expression { $$ = new div_assn(@$ , $1 , $3); }
	| unary_expression MOD_ASSIGN assignment_expression { $$ = new modu_assn(@$ , $1 , $3); }
	| unary_expression ADD_ASSIGN assignment_expression { $$ = new add_assn(@$ , $1 , $3); }
	| unary_expression SUB_ASSIGN assignment_expression { $$ = new sub_assn(@$ , $1 , $3); }
	| unary_expression LEFT_ASSIGN assignment_expression { $$ = new left_assn(@$ , $1 , $3); }
	| unary_expression RIGHT_ASSIGN assignment_expression { $$ = new right_assn(@$ , $1 , $3); }
	| unary_expression AND_ASSIGN assignment_expression { $$ = new and_assn(@$ , $1 , $3); }
	| unary_expression XOR_ASSIGN assignment_expression { $$ = new xor_assn(@$ , $1 , $3); }
	| unary_expression OR_ASSIGN assignment_expression { $$ = new or_assn(@$ , $1 , $3); }
	;

expression
	: assignment_expression { $$ = new expression_list(@$ , $1); }
	| expression ',' assignment_expression { $1->pushback($3); $$ = $1; }
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

declaration
	: declaration_specifiers ';' { $$ = new declaration(@$ , $1); }
	| declaration_specifiers init_declarator_list ';' { $$ = new declaration_init_decl(@$ , $1 , $2); }
	;

declaration_specifiers
	: storage_class_specifier { $$ = new declaration_specifiers(@$ , $1); }
	| storage_class_specifier declaration_specifiers { $2->pushback($1); $$ = $2; }
	| type_specifier { $$ = new declaration_specifiers(@$ , $1); }
	| type_specifier declaration_specifiers { $2->pushback($1); $$ = $2; }
	| type_qualifier { $$ = new declaration_specifiers(@$ , $1); }
	| type_qualifier declaration_specifiers { $2->pushback($1); $$ = $2; }
	| function_specifier { $$ = new declaration_specifiers(@$ , $1); }
	| function_specifier declaration_specifiers { $2->pushback($1); $$ = $2; }
	;

init_declarator_list
	: init_declarator { $$ = new init_declaration_list(@$ , $1); }
	| init_declarator_list ',' init_declarator { $1->pushback($3); $$ = $1; }
	;

init_declarator
	: declarator { $$ = new init_declarator(@$ , $1); }
	| declarator '=' initializer { $$ = new init_declarator_ini(@$ , $1 , $3); }
	;

storage_class_specifier
	: TYPEDEF { $$ = new storage_class_specifier(@$ , "TYPEDEF"); }
	| EXTERN { $$ = new storage_class_specifier(@$ , "EXTERN"); }
	| STATIC { $$ = new storage_class_specifier(@$ , "STATIC"); }
	| AUTO { $$ = new storage_class_specifier(@$ , "AUTO"); }
	| REGISTER { $$ = new storage_class_specifier(@$ , "REGISTER"); }
	;

type_specifier
	: VOID { $$ = new type_specifier(@$ , "VOID"); }
	| CHAR { $$ = new type_specifier(@$ , "CHAR"); }
	| SHORT { $$ = new type_specifier(@$ , "SHORT"); }
	| INT { $$ = new type_specifier(@$ , "INT"); }
	| LONG { $$ = new type_specifier(@$ , "LONG"); }
	| FLOAT { $$ = new type_specifier(@$ , "FLOAT"); }
	| DOUBLE { $$ = new type_specifier(@$ , "DOUBLE"); }
	| SIGNED { $$ = new type_specifier(@$ , "SIGNED"); }
	| UNSIGNED { $$ = new type_specifier(@$ , "UNSIGNED"); }
	| struct_or_union_specifier { $$ = $1; }
	| enum_specifier { $$ = $1; }
	| TYPE_NAME { $$ = new type_specifier(@$ , *$1); delete $1; }
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}' 
	{ $$ = new struct_union_spec_id_decl(@$ , $1 , new identifier(@$ , *$2) , $4); delete $2; }

	| struct_or_union '{' struct_declaration_list '}' { $$ = new struct_union_spec_decl(@$ , $1 , $3); }
	| struct_or_union IDENTIFIER { $$ = new struct_union_spec_id(@$ , $1 , new identifier(@$ , *$2)); delete $2; }
	;

struct_or_union
	: STRUCT { $$ = new struct_union(@$ , "struct"); }
	| UNION { $$ = new struct_union(@$ , "union"); }
	;

struct_declaration_list
	: struct_declaration { $$ = new struct_declaration_list(@$ , $1); }
	| struct_declaration_list struct_declaration { $1->pushback($2); $$ = $1; }
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';' { $$ = new struct_declaration(@$ , $1 , $2); }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list { $2->pushback($1); $$ = $2; }
	| type_specifier { $$ = new specifier_qualifier_list(@$ , $1); }
	| type_qualifier specifier_qualifier_list { $2->pushback($1); $$ = $2; }
	| type_qualifier { $$ = new specifier_qualifier_list(@$ , $1); }
	;

struct_declarator_list
	: struct_declarator { $$ = new struct_declarator_list(@$ , $1); }
	| struct_declarator_list ',' struct_declarator { $1->pushback($3); $$ = $1; }
	;

struct_declarator
	: declarator { $$ = new struct_declarator(@$ , $1); }
	| ':' constant_expression { $$ = new struct_declarator_padding(@$ , $2); }
	| declarator ':' constant_expression { $$ = new struct_declarator_size(@$ , $1 , $3); }
	;

enum_specifier
	: ENUM '{' enumerator_list '}' { $$ = new enum_spec(@$ , $3); }
	| ENUM IDENTIFIER '{' enumerator_list '}' { $$ = new enum_spec_id(@$ , new identifier(@2 , *$2) , $4); delete $2; }
	| ENUM '{' enumerator_list ',' '}' { $$ = new enum_spec(@$ , $3); }
	| ENUM IDENTIFIER '{' enumerator_list ',' '}' { $$ = new enum_spec_id(@$ , new identifier(@2 , *$2) , $4); delete $2; }
	| ENUM IDENTIFIER { $$ = new enum_declaration(@$ , new identifier(@2 , *$2)); delete $2; }
	;

enumerator_list
	: enumerator { $$ = new enumerator_list(@$ , $1); }
	| enumerator_list ',' enumerator { $1->pushback($3); $$ = $1; }
	;

enumerator
	: IDENTIFIER { $$ = new enumerator(@$ , new identifier(@1 , *$1) ); delete $1; }
	| IDENTIFIER '=' constant_expression { $$ = new enumerator_const_expr(@1 , new identifier(@1 , *$1) , $3); delete $1; }
	;

type_qualifier
	: CONST { $$ = new type_qualifier(@$ , "CONST"); }
	| RESTRICT { $$ = new type_qualifier(@$ , "RESTRICT"); }
	| VOLATILE { $$ = new type_qualifier(@$ , "VOLATILE"); }
	;

function_specifier
	: INLINE { $$ = new function_specifier(@$ , "INLINE"); }
	;

declarator
	: pointer direct_declarator { $$ = new declarator_pointer(@$ , $1, $2); }
	| direct_declarator { $$ = new declarator(@$ , $1); }
	;

direct_declarator
	: IDENTIFIER { $$ = new identifier(@$ , *$1); delete $1; }
	| direct_declarator '[' assignment_expression ']'{ $$ = new array_definition_size(@$ , $1 , $3); }
	| direct_declarator '[' ']' { $$ = new array_definition(@$ , $1); }
	| direct_declarator '(' ')' { $$ = new function_declarator(@$ , $1); }
	| direct_declarator '(' parameter_type_list ')' { $$ = new function_declarator_param(@$ , $1 , $3); }
	| direct_declarator '(' identifier_list ')' { $$ = new function_declarator_id_list(@$ , $1 , $3); }

	| '(' declarator ')' { $$ = new function_ptr(@$ , $2); }

	| direct_declarator '[' type_qualifier_list assignment_expression ']'
	{ $$ = new array_definition_type_qual_size(@$ , $1 , $3 , $4); }
	| direct_declarator '[' type_qualifier_list ']' { $$ = new array_definition_type_qual(@$ , $1 , $3); }
	;

pointer
	: '*' { $$ = new pointer_list(@$ , new pointer(@$) ); }
	| '*' pointer { $2->pushback( new pointer(@$) ); $$ = $2; }
	| '*' type_qualifier_list { $$ = new pointer_list(@$ , $2); }
	| '*' type_qualifier_list pointer { $3->pushback($2); $$ = $3; }
	;

type_qualifier_list
	: type_qualifier { $$ = new type_qualifier_list(@$ , $1); }
	| type_qualifier_list type_qualifier { $1->pushback($2);  $$ = $1; }
	;


parameter_type_list
	: parameter_list { $$ = $1; }
	| parameter_list ',' ELLIPSIS { $1->pushback(new ellipsis(@$)); $$ = $1; }
	;

parameter_list
	: parameter_declaration { $$ = new parameter_list(@$ , $1); }
	| parameter_list ',' parameter_declaration { $1->pushback($3); $$ = $1; }
	;

parameter_declaration
	: declaration_specifiers declarator { $$ = new parameter_full_decl(@$ , $1 , $2); }
	| declaration_specifiers { $$ = new parameter_decl(@$ , $1); /*used if only the function trace needs to be given*/}
	| declaration_specifiers abstract_declarator { $$ = new parameter_decl_abstract(@$ , $1 , $2); }
	;

identifier_list
	: IDENTIFIER { $$ = new identifier_list(@$ , new identifier(@$ , *$1)); delete $1; }
	| identifier_list ',' IDENTIFIER { $1->pushback(new identifier(@$ , *$3)); delete $3 ; $$ = $1; }
	;

type_name
	: specifier_qualifier_list { $$ = new type_name(@$ , $1); }
	| specifier_qualifier_list abstract_declarator { $$ = new type_name_abstract(@$ , $1 , $2); }
	;

abstract_declarator
	: pointer { $$ = $1; }
	| direct_abstract_declarator { $$ = new abstract_declarator(@$ , $1); }
	| pointer direct_abstract_declarator { $$ = new abstract_declarator_pointer(@$ , $1 , $2); }
	;

direct_abstract_declarator
	: '[' ']' { $$ = new unamed_empty_array(@$); }
	| '[' assignment_expression ']' { $$ = new unamed_empty_array_size(@$ , $2); }
	| direct_abstract_declarator '[' ']' { $$ = new array_decl_abstract(@$ , $1); }
	| direct_abstract_declarator '[' assignment_expression ']' { $$ = new array_decl_abstract_size(@$ , $1 , $3); }
	| '(' ')' { $$ = new unamed_empty_declaration(@$); }
	| '(' parameter_type_list ')' { $$ = new unamed_abstract_function_parameters(@$ , $2); }
	| direct_abstract_declarator '(' ')' { $$ = new abstract_function(@$ , $1); }
	| direct_abstract_declarator '(' parameter_type_list ')' { $$ = new abstract_function_parameters(@$ , $1 , $3); }
	| '(' abstract_declarator ')' { $$ = new abstract_function_pointer(@$ , $2); }
	;

initializer
	: assignment_expression { $$ = $1; }
	| '{' initializer_list '}' { $$ = new initialiser(@$ , $2); }
	| '{' initializer_list ',' '}' { $$ = new initialiser(@$ , $2); }
	;

initializer_list
	: initializer { $$ = new initialiser_list(@$ , $1); }
	| designation { $$ = new initialiser_list(@$ , $1); }
	| initializer_list ',' initializer { $1->pushback($3); $$ = $1; }
	| initializer_list ',' designation { $1->pushback($3); $$ = $1; }
	;

designation
	: designator_list '=' initializer { $$ = new designation(@$ , $1 , $3); }

designator_list
	: designator { $$ = new designator_list(@$ , $1); }
	| designator_list designator { $1->pushback($2); $$ = $1; }
	;

designator
	: '[' constant_expression ']' { $$ = new designator_constant_expr(@$ , $2); }
	| '.' IDENTIFIER { $$ = new designator_identifier(@$ , new identifier(@2 , *$2)); delete $2; }
	;

statement
	: labeled_statement { $$ = $1; }
	| compound_statement { $$ = $1; }
	| expression_statement { $$ = $1; }
	| selection_statement { $$ = $1; }
	| iteration_statement { $$ = $1; }
	| jump_statement { $$ = $1; }
	;

labeled_statement
	: IDENTIFIER ':' statement { $$ = new goto_target(@$ , new identifier(@$ , *$1) , $3); delete $1; }
	| CASE constant_expression ':' statement { $$ = new case_node(@$ , $2 , $4); }
	| DEFAULT ':' statement { $$ = new case_default_node(@$ , $3); }
	;

compound_statement
	: '{' '}' { $$ = new empty(@$); }
	| '{' block_item_list '}' { $$ = $2; }
	;

block_item_list
	: block_item { $$ = new block_item_list(@$ , $1); }
	| block_item_list block_item { $1->pushback($2) ; $$ = $1; }
	;

block_item
	: declaration { $$ = $1; }
	| statement { $$ = $1; }
	;

expression_statement
	: ';' { $$ = new empty(@$); }
	| expression ';' { $$ = $1; }
	;

selection_statement
	: IF '(' expression ')' statement { $$ = new if_node(@$ , $3 , $5); }
	| IF '(' expression ')' statement ELSE statement { $$ = new if_else_node(@$ , $3 , $5 , $7); }
	| SWITCH '(' expression ')' statement { $$ = new switch_node(@$ , $3 , $5); }
	;

iteration_statement
	: WHILE '(' expression ')' statement { $$ = new while_node(@$ , $3 , $5); }
	| DO statement WHILE '(' expression ')' ';' { $$ = new do_while_node(@$ , $2 , $5); }

	| FOR '(' expression_statement expression_statement ')' statement { $$ = new for_node_ext(@$ , $3 , $4 , $6); }
	| FOR '(' expression_statement expression_statement expression ')' statement { $$ = new for_node_ext_mod(@$ , $3 , $4 , $5 , $7); }
	| FOR '(' declaration expression_statement ')' statement { $$ = new for_node(@$ , $3 , $4 , $6); }
	| FOR '(' declaration expression_statement expression ')' statement { $$ = new for_node_mod(@$ , $3 , $4 , $5 , $7); }
	;

jump_statement
	: GOTO IDENTIFIER ';' { $$ = new jump_statement_goto(@$ , new identifier(@$ , *$2)); delete $2; }
	| CONTINUE ';' { $$ = new jump_statement_continue(@$); }
	| BREAK ';' { $$ = new jump_statement_break(@$); }
	| RETURN ';' { $$ = new jump_statement_ret(@$); }
	| RETURN expression ';' { $$ = new jump_statement_ret_expr(@$ , $2); }
	;

ROOT
	:translation_unit { root_node = $1; }

translation_unit
	: external_declaration { $$ = new translation_unit(@$ , $1); }
	| translation_unit external_declaration { $1->pushback($2); $$ = $1; }
	;

external_declaration
	: function_definition { $$ = $1; }
	| declaration { $$ = $1; }
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement { $$ = new function_definition_decl_list(@$ , $1 , $2 , $3 , $4); }
	| declaration_specifiers declarator compound_statement { $$ = new function_definition(@$ , $1 , $2 , $3); }
	;

declaration_list
	: declaration { $$ = new declaration_list(@$ , $1); }
	| declaration_list declaration { $1->pushback($2); $$ = $1; }
	;


%%

void yyerror(char const *s) {
	std::cout << "got error at line: " << yylineno << std::endl;
	errors::add_err(new error(yylloc , s , false)); 
	errors::die(s);
}


node *parseAST(std::string file_name) {

	yyin = fopen(file_name.c_str(), "r");

	if(yyin == NULL){
		errors::die("Failure in opening source file");
	}

	root_node = nullptr;
	yyparse();
	return root_node;
}


