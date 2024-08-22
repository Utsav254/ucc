%option noyywrap
%option nounput
%option yylineno
%{	
	//from: https://www.quut.com/c/ANSI-C-grammar-l-1999.html
	extern "C" int fileno(FILE *stream);

	#include "parser.tab.hpp"
	#include "context/context.hpp"
	#include <stdio.h>
	#include <string.h>
	#include <string>
	#include <iostream>

	//local functions forward declaration

	int check_type(const char *s);
	char extract_char_value(const char *text);

	//previous token variable
	yytokentype prev = YYUNDEF;

	//location handling

	int yycolumn;

	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
		yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng + 1; \
		yycolumn += yyleng;\
		
%}

D	[0-9]
L	[a-zA-Z_]
H	[a-fA-F0-9]
E	([Ee][+-]?{D}+)
P	([Pp][+-]?{D}+)
FS	(f|F|l|L)
IS  ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))


%%
"/*"			{  }
"//"[^\n]*      { /* consume //-comment */ }

"auto"			{ prev = AUTO; return(AUTO); }
"break"			{ prev = BREAK; return(BREAK); }
"case"			{ prev = CASE; return(CASE); }
"char"			{ prev = CHAR; return(CHAR); }
"const"			{ prev = CONST;  return(CONST); }
"continue"		{ prev = CONTINUE;  return(CONTINUE); }
"default"		{ prev = DEFAULT;  return(DEFAULT); }
"do"			{ prev = DO;  return(DO); }
"double"		{ prev = DOUBLE;  return(DOUBLE); }
"else"			{ prev = ELSE;  return(ELSE); }
"enum"			{ prev = ENUM;  return(ENUM); }
"extern"		{ prev = EXTERN;  return(EXTERN); }
"float"			{ prev = FLOAT;  return(FLOAT); }
"for"			{ prev = FOR;  return(FOR); }
"goto"			{ prev = GOTO;  return(GOTO); }
"if"			{ prev = IF;  return(IF); }
"inline"		{ prev = INLINE;  return(INLINE); }
"int"			{ prev = INT;  return(INT); }
"long"			{ prev = LONG;  return(LONG); }
"register"		{ prev = REGISTER;  return(REGISTER); }
"restrict"		{ prev = RESTRICT; return(RESTRICT); }
"return"		{ prev = RETURN;  return(RETURN); }
"short"			{ prev = SHORT;  return(SHORT); }
"signed"		{ prev = SIGNED;  return(SIGNED); }
"sizeof"		{ prev = SIZEOF;  return(SIZEOF); }
"static"		{ prev = STATIC;  return(STATIC); }
"struct"		{ prev = STRUCT;  return(STRUCT); }
"switch"		{ prev = SWITCH;  return(SWITCH); }
"typedef"		{ prev = TYPEDEF;  return(TYPEDEF); }
"union"			{ prev = UNION;  return(UNION); }
"unsigned"		{ prev = UNSIGNED;  return(UNSIGNED); }
"void"			{ prev = VOID;  return(VOID); }
"volatile"		{ prev = VOLATILE;  return(VOLATILE); }
"while"			{ prev = WHILE; return(WHILE); }

{L}({L}|{D})*		{ yylval.string = new std::string(yytext); return(check_type(yytext)); }

0[xX]{H}+{IS}?		{ prev = INT_CONSTANT; yylval.number_int = (int)strtol(yytext , NULL , 0); return(INT_CONSTANT); }
0[0-7]*{IS}?		{ prev = INT_CONSTANT; yylval.number_int = (int)strtol(yytext , NULL , 0); return(INT_CONSTANT); }
[1-9]{D}*{IS}?		{ prev = INT_CONSTANT; yylval.number_int = (int)strtol(yytext , NULL , 0); return(INT_CONSTANT); }
L?'(\\.|[^\\'\n])+'	{ prev = CHAR_CONSTANT; yylval.letter_char = extract_char_value(yytext); return(CHAR_CONSTANT); }

{D}+{E}{FS}?		{ prev = FLOAT_CONSTANT; yylval.number_float = strtod(yytext, NULL); return(FLOAT_CONSTANT); }
{D}*"."{D}+{E}?{FS}?	{ prev = FLOAT_CONSTANT; yylval.number_float = strtod(yytext , NULL); return(FLOAT_CONSTANT); }
{D}+"."{D}*{E}?{FS}?	{ prev = FLOAT_CONSTANT; yylval.number_float = strtod(yytext , NULL); return(FLOAT_CONSTANT); }

0[xX]{H}+{P}{FS}?	{ errors::die("does not handle hex floating constants yet");}
0[xX]{H}*"."{H}+{P}?{FS}?     { errors::die("does not handle hex floating constants yet");}
0[xX]{H}+"."{H}*{P}?{FS}?     { errors::die("does not handle hex floating constants yet");}


L?\"(\\.|[^\\"\n])*\"	{ prev = STRING_LITERAL; yylval.string = new std::string(yytext); return(STRING_LITERAL); }

L?\"[^\"\n]*$			{	
							prev = STRING_LITERAL;
							errors::add_err(new error(yylloc , "unterminated string" , true)); 
							yylval.string = new std::string(yytext); 
							return(STRING_LITERAL); 
						}

"..."			{ prev = ELLIPSIS; return(ELLIPSIS); }
">>="			{ prev = RIGHT_ASSIGN; return(RIGHT_ASSIGN); }
"<<="			{ prev = LEFT_ASSIGN; return(LEFT_ASSIGN); }
"+="			{ prev = ADD_ASSIGN; return(ADD_ASSIGN); }
"-="			{ prev = SUB_ASSIGN; return(SUB_ASSIGN); }
"*="			{ prev = MUL_ASSIGN; return(MUL_ASSIGN); }
"/="			{ prev = DIV_ASSIGN; return(DIV_ASSIGN); }
"%="			{ prev = MOD_ASSIGN; return(MOD_ASSIGN); }
"&="			{ prev = AND_ASSIGN; return(AND_ASSIGN); }
"^="			{ prev = XOR_ASSIGN; return(XOR_ASSIGN); }
"|="			{ prev = OR_ASSIGN; return(OR_ASSIGN); }
">>"			{ prev = RIGHT_OP; return(RIGHT_OP); }
"<<"			{ prev = LEFT_OP; return(LEFT_OP); }
"++"			{ prev = INC_OP; return(INC_OP); }
"--"			{ prev = DEC_OP; return(DEC_OP); }
"->"			{ prev = PTR_OP; return(PTR_OP); }
"&&"			{ prev = AND_OP; return(AND_OP); }
"||"			{ prev = OR_OP; return(OR_OP); }
"<="			{ prev = LE_OP; return(LE_OP); }
">="			{ prev = GE_OP; return(GE_OP); }
"=="			{ prev = EQ_OP; return(EQ_OP); }
"!="			{ prev = NE_OP; return(NE_OP); }
";"				{ prev = YYUNDEF; return(';'); }
("{"|"<%")		{ prev = YYUNDEF; return('{'); }
("}"|"%>")		{ prev = YYUNDEF; return('}'); }
","				{ prev = YYUNDEF; return(','); }
":"				{ prev = YYUNDEF; return(':'); }
"="				{ prev = YYUNDEF; return('='); }
"("				{ prev = YYUNDEF; return('('); }
")"				{ prev = YYUNDEF; return(')'); }
("["|"<:")		{ prev = YYUNDEF; return('['); }
("]"|":>")		{ prev = YYUNDEF; return(']'); }
"."				{ prev = YYUNDEF; return('.'); }
"&"				{ prev = YYUNDEF; return('&'); }
"!"				{ prev = YYUNDEF; return('!'); }
"~"				{ prev = YYUNDEF; return('~'); }
"-"				{ prev = YYUNDEF; return('-'); }
"+"				{ prev = YYUNDEF; return('+'); }
"*"				{ prev = YYUNDEF; return('*'); }
"/"				{ prev = YYUNDEF; return('/'); }
"%"				{ prev = YYUNDEF; return('%'); }
"<"				{ prev = YYUNDEF; return('<'); }
">"				{ prev = YYUNDEF; return('>'); }
"^"				{ prev = YYUNDEF; return('^'); }
"|"				{ prev = YYUNDEF; return('|'); }
"?"				{ prev = YYUNDEF; return('?'); }
[\v\f\t]		{ }
[\n]			{ yycolumn = 1; }
#.*\n			{ }
.				{ }

%%


int check_type(const char *s) {
	//first check if previous token was a struct union enum
	//	- this must be an identifier if it is string token
	//if it is an identifier then this should be the case where it is a struct identifier identifier
	//this helps with typedefs where the alias is the same as the typename
	if (prev == STRUCT || prev == IDENTIFIER || prev == ENUM || prev == TYPE_NAME) {
		prev = IDENTIFIER;
		return IDENTIFIER;
	}
	else if(!context::is_member_types_tmp(std::string(s))) {
		prev = IDENTIFIER;
		return IDENTIFIER;
	}
	else {
		prev = TYPE_NAME;
		return TYPE_NAME;
	}
}


char extract_char_value(const char *text) {
    char value;
    int len = strlen(text);

    if (text[0] == 'L') text++;

    if (len == 3 && text[0] == '\'' && text[2] == '\'') value = text[1]; 

	else if (len > 3 && text[0] == '\'' && text[1] == '\\' && text[len-1] == '\'') {
        // Escape sequences
        switch (text[2]) {
            case 'a': value = '\a'; break;
            case 'b': value = '\b'; break;
            case 'f': value = '\f'; break;
            case 'n': value = '\n'; break;
            case 'r': value = '\r'; break;
            case 't': value = '\t'; break;
            case 'v': value = '\v'; break;
            case '\\': value = '\\'; break;
            case '\'': value = '\''; break;
            case '\"': value = '\"'; break;
            case '\?': value = '\?'; break;
            case '0': value = '\0'; break;
            case 'x':
                // Handle hex escape sequence
                value = (char) strtol(text + 3, NULL, 16);
                break;
            default:
                if (text[2] >= '0' && text[2] <= '7') {
                    // Handle octal escape sequence
                    value = (char) strtol(text + 2, NULL, 8);
                } else {
                    // Unsupported escape sequence, not required for now
                    value = text[2];
                }
                break;
        }
    } else {
        // Handle multi-character constants ... not required for now
        value = text[1];
    }

    return value;
}

