%code requires{
	//from: https://www.quut.com/c/ANSI-C-grammar-y-1999.html
    #include "ast/ast.hpp"
	#include "cli.hpp"

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
%type <Node> conditional_expression assignment_expression expression constant_expression declaration declaration_specifiers
%type <Node> init_declarator type_specifier struct_declaration_list struct_declaration specifier_qualifier_list struct_declarator_list
%type <Node> struct_declarator enum_specifier enumerator declarator direct_declarator pointer parameter_declaration
%type <Node> identifier_list type_name abstract_declarator direct_abstract_declarator initializer initializer_list statement labeled_statement
%type <Node> compound_statement expression_statement selection_statement iteration_statement jump_statement
%type <Node> unary_operator assignment_operator storage_class_specifier

%type <Nodes> declaration_list init_declarator_list translation_unit parameter_list argument_expression_list enumerator_list

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
	| STRING_LITERAL
	| '(' expression ')' {$$ = $2;}
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']' { /*array indexing*/}
	| postfix_expression '(' ')' {/*function call*/}
	| postfix_expression '(' argument_expression_list ')' {/*function call with arguments*/}
	| postfix_expression '.' IDENTIFIER {/*member of struct*/}
	| postfix_expression PTR_OP IDENTIFIER {/*member of struct pointer*/}
	| postfix_expression INC_OP {/*increment a value*/}
	| postfix_expression DEC_OP {/*decrement a value*/}
	| '(' type_name ')' '{' initializer_list '}' {/**/}
	| '(' type_name ')' '{' initializer_list ',' '}'
	;

argument_expression_list
	: assignment_expression {/*function call argument can be: add(x = 9 , y = 1)*/}
	| argument_expression_list ',' assignment_expression { /*multiple function call arguments*/}
	;

unary_expression
	: postfix_expression {/*for e.g. x++*/}
	| INC_OP unary_expression {/*for e.g. ++x*/}
	| DEC_OP unary_expression {/*for e.g. --x*/}
	| unary_operator cast_expression {/*arithmetic after casting... requires type checking*/}
	| SIZEOF unary_expression {/*for e.g. sizeof(x) , sizeof(x++) etc*/}
	| SIZEOF '(' type_name ')' {/*for e.g. sizeof(int)*/}
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression {/*the order of the expressions will cascade down...*/}
	| '(' type_name ')' cast_expression { /*cast operation for e.g. (int) ... requires type checking and stuff*/}
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression {/*x += 3*/}
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression
	| expression ',' assignment_expression { /*used in the case of multi var declaration: x = 0 , y , z = 1*/}
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	| function_specifier
	| function_specifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| struct_or_union_specifier
	| enum_specifier
	| TYPE_NAME
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
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
	: CONST
	| RESTRICT
	| VOLATILE
	;

function_specifier
	: INLINE
	;

declarator
	: pointer direct_declarator
	| direct_declarator
	;


direct_declarator
	: IDENTIFIER
	| '(' declarator ')'
	| direct_declarator '[' type_qualifier_list assignment_expression ']'
	| direct_declarator '[' type_qualifier_list ']'
	| direct_declarator '[' assignment_expression ']'
	| direct_declarator '[' STATIC type_qualifier_list assignment_expression ']'
	| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'
	| direct_declarator '[' type_qualifier_list '*' ']'
	| direct_declarator '[' '*' ']' { /*wierd c99 feature for vari array lengths in function forward declarations*/}
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_type_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
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
	: parameter_list
	| parameter_list ',' ELLIPSIS {/*variadic functions ... low priority feature*/}
	;

parameter_list
	: parameter_declaration {/*for function defintions/declarations*/}
	| parameter_list ',' parameter_declaration { /*multiple function parameters*/}
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
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
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' block_item_list '}' {/* scope ... */}
	;

block_item_list
	: block_item
	| block_item_list block_item
	;

block_item
	: declaration
	| statement { /*encapsulates the body sections of if else functions and all that */}
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	| FOR '(' declaration expression_statement ')' statement
	| FOR '(' declaration expression_statement expression ')' statement
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

ROOT
	:translation_unit { root_node = $1; }

translation_unit
	: external_declaration { $$ = new nodelist($1); }
	| translation_unit external_declaration { $1->pushback($2); $$ = $1; }
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement {/* function defintion with paramaters*/}
	| declaration_specifiers declarator compound_statement
	;

declaration_list
	: declaration
	| declaration_list declaration
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


