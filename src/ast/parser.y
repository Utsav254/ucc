%code requires{
	//from: https://www.quut.com/c/ANSI-C-grammar-y-1999.html
    #include "ast.hpp"
	#include "../cli.hpp"

    extern node *root_node;
    extern FILE *yyin;
    int yylex(void);
    void yyerror(const char *);
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
%type <Node> equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <Node> conditional_expression assignment_expression constant_expression declaration 
%type <Node> init_declarator type_specifier struct_declaration 
%type <Node> struct_declarator enum_specifier enumerator declarator direct_declarator pointer parameter_declaration
%type <Node> type_name abstract_declarator direct_abstract_declarator initializer statement labeled_statement
%type <Node> compound_statement expression_statement selection_statement iteration_statement jump_statement
%type <Node> storage_class_specifier block_item type_qualifier function_specifier struct_or_union_specifier struct_or_union

%type <Nodes> declaration_list init_declarator_list translation_unit parameter_type_list parameter_list argument_expression_list enumerator_list
%type <Nodes> block_item_list declaration_specifiers expression identifier_list struct_declaration_list specifier_qualifier_list struct_declarator_list
%type <Nodes> initializer_list

%type <number_int> INT_CONSTANT
%type <number_float> FLOAT_CONSTANT
%type <letter_char> CHAR_CONSTANT
%type <string> IDENTIFIER STRING_LITERAL

%start ROOT

%%

primary_expression
	: IDENTIFIER { $$ = new identifier(*$1); delete $1;}
	| INT_CONSTANT { $$ = new int_constant($1); }
	| FLOAT_CONSTANT { $$ = new float_constant($1); }
	| CHAR_CONSTANT { $$ = new char_constant($1); }
	| STRING_LITERAL {}
	| '(' expression ')' {$$ = $2;}
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression '[' expression ']' { $$ = new array_index($1 , $3); }
	| postfix_expression '(' ')' { $$ = new function_call($1); }
	| postfix_expression '(' argument_expression_list ')' { $$ = new function_call_arg($1 , $3); }

	| postfix_expression '.' IDENTIFIER {/*member of struct*/}
	| postfix_expression PTR_OP IDENTIFIER {/*member of struct pointer*/}

	| postfix_expression INC_OP { $$ = new postfix_incr($1); }
	| postfix_expression DEC_OP { $$ = new postfix_decr($1); }

	| '(' type_name ')' '{' initializer_list '}'
	| '(' type_name ')' '{' initializer_list ',' '}'
	;

argument_expression_list
	: assignment_expression { $$ = new nodelist($1 , list_type::ARGUMENT_EXPR); }
	| argument_expression_list ',' assignment_expression { $1->pushback($3); $$ = $1; }
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression { $$ = new unary_incr($2); }
	| DEC_OP unary_expression { $$ = new unary_decr($2); }
	| SIZEOF unary_expression {/*for e.g. sizeof(x) , sizeof(x++) etc*/}
	| SIZEOF '(' type_name ')' {/*for e.g. sizeof(int)*/}

	| '&' cast_expression {/*arithmetic after casting... requires type checking*/}
	| '*' cast_expression
	| '+' cast_expression
	| '-' cast_expression
	| '~' cast_expression
	| '!' cast_expression
	;

cast_expression
	: unary_expression { $$ = $1; }
	| '(' type_name ')' cast_expression { }
	;

multiplicative_expression
	: cast_expression { $$ = $1; }
	| multiplicative_expression '*' cast_expression {$$ = new mul($1,$3);}
	| multiplicative_expression '/' cast_expression {$$ = new divi($1,$3);}
	| multiplicative_expression '%' cast_expression {$$ = new modulo($1,$3);}
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression {$$ = new add($1,$3);}
	| additive_expression '-' multiplicative_expression {$$ = new sub($1,$3);}
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression {$$ = new left_shift($1,$3);}
	| shift_expression RIGHT_OP additive_expression {$$ = new right_shift($1,$3);}
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression {$$ = new less_than($1,$3);}
	| relational_expression '>' shift_expression {$$ = new greater_than($1,$3);}
	| relational_expression LE_OP shift_expression {$$ = new less_eq_than($1,$3);}
	| relational_expression GE_OP shift_expression {$$ = new greater_eq_than($1,$3);}
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQ_OP relational_expression {$$ = new equality($1,$3);}
	| equality_expression NE_OP relational_expression {$$ = new not_equal($1,$3);}
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression '&' equality_expression {$$ = new andop($1,$3);}
	;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression '^' and_expression {$$ = new xorop($1,$3);}
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression {$$ = new orop($1,$3);}
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression {$$ = new log_andop($1,$3);}
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression {$$ = new log_orop($1,$3);}
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression { $$ = new conditional_expression($1 , $3 , $5); }
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression '=' assignment_expression { $$ = new assn_op($1 , $3 , assn::EQUALS); }
	| unary_expression MUL_ASSIGN assignment_expression { $$ = new assn_op($1 , $3 , assn::MUL); }
	| unary_expression DIV_ASSIGN assignment_expression { $$ = new assn_op($1 , $3 , assn::DIV); }
	| unary_expression MOD_ASSIGN assignment_expression { $$ = new assn_op($1 , $3 , assn::MOD); }
	| unary_expression ADD_ASSIGN assignment_expression { $$ = new assn_op($1 , $3 , assn::ADD); }
	| unary_expression SUB_ASSIGN assignment_expression { $$ = new assn_op($1 , $3 , assn::SUB); }
	| unary_expression LEFT_ASSIGN assignment_expression { $$ = new assn_op($1 , $3 , assn::LEFT); }
	| unary_expression RIGHT_ASSIGN assignment_expression { $$ = new assn_op($1 , $3 , assn::RIGHT); }
	| unary_expression AND_ASSIGN assignment_expression { $$ = new assn_op($1 , $3 , assn::AND); }
	| unary_expression XOR_ASSIGN assignment_expression { $$ = new assn_op($1 , $3 , assn::XOR); }
	| unary_expression OR_ASSIGN assignment_expression { $$ = new assn_op($1 , $3 , assn::OR); }
	;

expression
	: assignment_expression { $$ = new nodelist($1 , list_type::EXPRESSION); }
	| expression ',' assignment_expression { $1->pushback($3); $$ = $1; }
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

declaration
	: declaration_specifiers ';' { $$ = new declaration($1); }
	| declaration_specifiers init_declarator_list ';' { $$ = new declaration_init_decl($1 , $2); }
	;

declaration_specifiers
	: storage_class_specifier { $$ = new nodelist($1 , list_type::DECL_SPEC); }
	| storage_class_specifier declaration_specifiers { $2->pushback($1); $$ = $2; }
	| type_specifier { $$ = new nodelist($1 , list_type::DECL_SPEC); }
	| type_specifier declaration_specifiers { $2->pushback($1); $$ = $2; }
	| type_qualifier { $$ = new nodelist($1 , list_type::DECL_SPEC); }
	| type_qualifier declaration_specifiers { $2->pushback($1); $$ = $2; }
	| function_specifier { $$ = new nodelist($1 , list_type::DECL_SPEC); }
	| function_specifier declaration_specifiers { $2->pushback($1); $$ = $2; }
	;

init_declarator_list
	: init_declarator { $$ = new nodelist($1 , list_type::INIT_DECL); }
	| init_declarator_list ',' init_declarator { $1->pushback($3); $$ = $1; }
	;

init_declarator
	: declarator { $$ = new init_declarator($1); }
	| declarator '=' initializer { $$ = new init_declarator_ini($1 , $3); }
	;

storage_class_specifier
	: TYPEDEF { $$ = new storage_class_specifier(storage_specifiers::TYPEDEF); }
	| EXTERN { $$ = new storage_class_specifier(storage_specifiers::EXTERN); }
	| STATIC { $$ = new storage_class_specifier(storage_specifiers::STATIC); }
	| AUTO { $$ = new storage_class_specifier(storage_specifiers::AUTO); }
	| REGISTER { $$ = new storage_class_specifier(storage_specifiers::REGISTER); }
	;

type_specifier
	: VOID { $$ = new type_specifier(type_specifiers::VOID); }
	| CHAR { $$ = new type_specifier(type_specifiers::CHAR); }
	| SHORT { $$ = new type_specifier(type_specifiers::SHORT); }
	| INT { $$ = new type_specifier(type_specifiers::INT); }
	| LONG { $$ = new type_specifier(type_specifiers::LONG); }
	| FLOAT { $$ = new type_specifier(type_specifiers::FLOAT); }
	| DOUBLE { $$ = new type_specifier(type_specifiers::DOUBLE); }
	| SIGNED { $$ = new type_specifier(type_specifiers::SIGNED); }
	| UNSIGNED { $$ = new type_specifier(type_specifiers::UNSIGNED); }
	| struct_or_union_specifier { $$ = $1; }
	| enum_specifier { $$ = $1; }
	| TYPE_NAME { $$ = new type_specifier(type_specifiers::TYPEDEF_NAME); }
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}' { $$ = new struct_union_spec_id_decl($1 , new identifier(*$2) , $4); delete $2; }
	| struct_or_union '{' struct_declaration_list '}' { $$ = new struct_union_spec_decl($1 , $3); }
	| struct_or_union IDENTIFIER { $$ = new struct_union_spec_id($1 , new identifier(*$2)); delete $2; }
	;

struct_or_union
	: STRUCT { $$ = new struct_union(structorunion::STRUCT); }
	| UNION { $$ = new struct_union(structorunion::UNION); }
	;

struct_declaration_list
	: struct_declaration { $$ = new nodelist($1 , list_type::STRUCT_DECLARATION); }
	| struct_declaration_list struct_declaration { $1->pushback($2); $$ = $1; }
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';' { $$ = new struct_declaration($1 , $2); }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list { $2->pushback($1); $$ = $2; }
	| type_specifier { $$ = new nodelist($1 , list_type::SPEC_QUAL); }
	| type_qualifier specifier_qualifier_list { $2->pushback($1); $$ = $2; }
	| type_qualifier { $$ = new nodelist($1 , list_type::SPEC_QUAL); }
	;

struct_declarator_list
	: struct_declarator { $$ = new nodelist($1 , list_type::STRUCT_DECLARATOR); }
	| struct_declarator_list ',' struct_declarator { $1->pushback($3); $$ = $1; }
	;

struct_declarator
	: declarator { $$ = new struct_declarator($1); }
	| ':' constant_expression { $$ = new struct_declarator_padding($2); }
	| declarator ':' constant_expression { $$ = new struct_declarator_size($1 , $3); }
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM '{' enumerator_list ',' '}'
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

type_qualifier
	: CONST { $$ = new type_qualifier(type_qualifiers::CONST); }
	| RESTRICT { $$ = new type_qualifier(type_qualifiers::RESTRICT); }
	| VOLATILE { $$ = new type_qualifier(type_qualifiers::VOLATILE); }
	;

function_specifier
	: INLINE { $$ = new function_specifier(function_specifiers::INLINE); }
	;

declarator
	: pointer direct_declarator { $$ = new declarator_pointer($1, $2); }
	| direct_declarator { $$ = new declarator($1); }
	;


direct_declarator
	: IDENTIFIER { $$ = new identifier(*$1); delete $1; }
	| direct_declarator '[' assignment_expression ']'{ $$ = new array_definition_size($1 , $3); }
	| direct_declarator '[' ']' { $$ = new array_definition($1); }
	| direct_declarator '(' ')' { $$ = new function_declarator($1); }
	| direct_declarator '(' parameter_type_list ')' { $$ = new function_declarator_param($1 , $3); }
	| direct_declarator '(' identifier_list ')' { $$ = new function_declarator_id_list($1 , $3); }

	| direct_declarator '[' '*' ']' { /*wierd c99 feature for vari array lengths in function forward declarations*/}
	| '(' declarator ')' { /*function pointer stuff*/}

	| direct_declarator '[' type_qualifier_list assignment_expression ']' {/*this probably can be deleted*/}
	| direct_declarator '[' type_qualifier_list ']' { /*this can probably be deleted*/}
	| direct_declarator '[' STATIC type_qualifier_list assignment_expression ']'
	| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'
	| direct_declarator '[' type_qualifier_list '*' ']'
	;

pointer
	: '*'
	| '*' type_qualifier_list
	| '*' pointer
	| '*' type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;


parameter_type_list
	: parameter_list { $$ = $1; }
	| parameter_list ',' ELLIPSIS { $1->pushback( new ellipsis()); $$ = $1; }
	;

parameter_list
	: parameter_declaration { $$ = new nodelist($1 , list_type::PARAMETER); }
	| parameter_list ',' parameter_declaration { $1->pushback($3); $$ = $1; }
	;

parameter_declaration
	: declaration_specifiers declarator { $$ = new parameter_full_decl($1 , $2); }
	| declaration_specifiers { $$ = new parameter_decl($1); /*used if only the function trace needs to be given*/}

	| declaration_specifiers abstract_declarator {/*low priority feature*/}
	;

identifier_list
	: IDENTIFIER { $$ = new nodelist( new identifier(*$1) , list_type::IDENTIFIER); delete $1; }
	| identifier_list ',' IDENTIFIER { $1->pushback(new identifier(*$3)); delete $3 ; $$ = $1; }
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' { /*function pointers stuff ... low priority*/}
	| '[' ']'
	| '[' assignment_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' assignment_expression ']'
	| '[' '*' ']'
	| direct_abstract_declarator '[' '*' ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}' { /*array initialiser */}
	;

initializer_list
	: initializer
	| designation initializer
	| initializer_list ',' initializer
	| initializer_list ',' designation initializer
	;

designation
	: designator_list '='
	;

designator_list
	: designator
	| designator_list designator
	;

designator
	: '[' constant_expression ']'
	| '.' IDENTIFIER
	;

statement
	: labeled_statement { $$ = new statement($1 , statement_type::LABELLED); }
	| compound_statement { $$ = new statement($1 , statement_type::COMPOUND); }
	| expression_statement { $$ = new statement($1 , statement_type::EXPRESSION); }
	| selection_statement { $$ = new statement($1 , statement_type::SELECTION); }
	| iteration_statement { $$ = new statement($1 , statement_type::ITERATION); }
	| jump_statement { $$ = new statement($1 , statement_type::JUMP); }
	;

labeled_statement
	: IDENTIFIER ':' statement { $$ = new goto_target(new identifier(*$1) , $3); delete $1; }
	| CASE constant_expression ':' statement { $$ = new case_node($2 , $4); }
	| DEFAULT ':' statement { $$ = new case_default_node($3); }
	;

compound_statement
	: '{' '}' { $$ = new empty(); }
	| '{' block_item_list '}' { $$ = $2; }
	;

block_item_list
	: block_item { $$ = new nodelist($1 , list_type::BLOCK); }
	| block_item_list block_item { $1->pushback($2) ; $$ = $1; }
	;

block_item
	: declaration { $$ = $1; }
	| statement { $$ = $1; }
	;

expression_statement
	: ';' { $$ = new empty(); }
	| expression ';' { $$ = $1; }
	;

selection_statement
	: IF '(' expression ')' statement { $$ = new if_node( $3 , $5); }
	| IF '(' expression ')' statement ELSE statement { $$ = new if_else_node($3 , $5 , $7); }
	| SWITCH '(' expression ')' statement { $$ = new switch_node($3 , $5); }
	;

iteration_statement
	: WHILE '(' expression ')' statement { $$ = new while_node($3 , $5); }
	| DO statement WHILE '(' expression ')' ';' { $$ = new do_while_node($2 , $5); }

	| FOR '(' expression_statement expression_statement ')' statement { $$ = new for_node_ext($3 , $4 , $6); }
	| FOR '(' expression_statement expression_statement expression ')' statement { $$ = new for_node_ext_mod($3 , $4 , $5 , $7); }
	| FOR '(' declaration expression_statement ')' statement { $$ = new for_node($3 , $4 , $6); }
	| FOR '(' declaration expression_statement expression ')' statement { $$ = new for_node_mod($3 , $4 , $5 , $7); }
	;

jump_statement
	: GOTO IDENTIFIER ';' { $$ = new jump_statement_goto(jump_type::GOTO , new identifier(*$2)); delete $2; }
	| CONTINUE ';' { $$ = new jump_statement(jump_type::CONTINUE); }
	| BREAK ';' { $$ = new jump_statement(jump_type::BREAK); }
	| RETURN ';' { $$ = new jump_statement(jump_type::RETURN); }
	| RETURN expression ';' { $$ = new jump_statement_ret_expr(jump_type::RETURN , $2); }
	;

ROOT
	:translation_unit { root_node = $1; }

translation_unit
	: external_declaration { $$ = new nodelist($1 , list_type::TRANSLATION_UNIT); }
	| translation_unit external_declaration { $1->pushback($2); $$ = $1; }
	;

external_declaration
	: function_definition { $$ = $1; }
	| declaration { $$ = $1; }
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement { $$ = new function_definition_decl_list($1 , $2 , $3 , $4); }
	| declaration_specifiers declarator compound_statement { $$ = new function_definition($1 , $2 , $3); }
	;

declaration_list
	: declaration { $$ = new nodelist($1 , list_type::DECLARATION); }
	| declaration_list declaration { $1->pushback($2); $$ = $1; }
	;


%%

extern char yytext[];
extern int err_column;
extern std::string err_string;

void yyerror(char const *s) {
	//avoid the unused param warning
	s = s;
	die(err_string , errcode::SYNTAX);
}


node *parseAST(std::string file_name) {

	yyin = fopen(file_name.c_str(), "r");

	if(yyin == NULL){
		die("Failure in opening source file" , errcode::FILE_IO);
	}

	root_node = nullptr;
	yyparse();
	return root_node;
}


