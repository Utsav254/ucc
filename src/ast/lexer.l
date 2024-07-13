%option noyywrap
%option nounput
%option yylineno
%{	
	//from: https://www.quut.com/c/ANSI-C-grammar-l-1999.html
	extern "C" int fileno(FILE *stream);

	#include "parser.tab.hpp"
	#include "context.hpp"
	#include <stdio.h>
	#include <string.h>
	#include <string>

	//local functions forward declaration

	int check_type(const char *s);
	char extract_char_value(const char *text);

	//location handling

	int yycolumn;

	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
		yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng + 1; \
		yycolumn += yyleng;
		
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

"auto"			{ return(AUTO); }
"break"			{ return(BREAK); }
"case"			{ return(CASE); }
"char"			{ return(CHAR); }
"const"			{ return(CONST); }
"continue"		{ return(CONTINUE); }
"default"		{ return(DEFAULT); }
"do"			{ return(DO); }
"double"		{ return(DOUBLE); }
"else"			{ return(ELSE); }
"enum"			{ return(ENUM); }
"extern"		{ return(EXTERN); }
"float"			{ return(FLOAT); }
"for"			{ return(FOR); }
"goto"			{ return(GOTO); }
"if"			{ return(IF); }
"inline"		{ return(INLINE); }
"int"			{ return(INT); }
"long"			{ return(LONG); }
"register"		{ return(REGISTER); }
"restrict"		{ return(RESTRICT); }
"return"		{ return(RETURN); }
"short"			{ return(SHORT); }
"signed"		{ return(SIGNED); }
"sizeof"		{ return(SIZEOF); }
"static"		{ return(STATIC); }
"struct"		{ return(STRUCT); }
"switch"		{ return(SWITCH); }
"typedef"		{ return(TYPEDEF); }
"union"			{ return(UNION); }
"unsigned"		{ return(UNSIGNED); }
"void"			{ return(VOID); }
"volatile"		{ return(VOLATILE); }
"while"			{ return(WHILE); }

{L}({L}|{D})*		{ yylval.string = new std::string(yytext); return(check_type(yytext)); }

0[xX]{H}+{IS}?		{ yylval.number_int = (int)strtol(yytext , NULL , 0); return(INT_CONSTANT); }
0[0-7]*{IS}?		{ yylval.number_int = (int)strtol(yytext , NULL , 0); return(INT_CONSTANT); }
[1-9]{D}*{IS}?		{ yylval.number_int = (int)strtol(yytext , NULL , 0); return(INT_CONSTANT); }
L?'(\\.|[^\\'\n])+'	{ yylval.letter_char = extract_char_value(yytext); return(CHAR_CONSTANT); }

{D}+{E}{FS}?		{ yylval.number_float = strtod(yytext, NULL); return(FLOAT_CONSTANT); }
{D}*"."{D}+{E}?{FS}?	{ yylval.number_float = strtod(yytext , NULL); return(FLOAT_CONSTANT); }
{D}+"."{D}*{E}?{FS}?	{ yylval.number_float = strtod(yytext , NULL); return(FLOAT_CONSTANT); }

0[xX]{H}+{P}{FS}?	{ errors::die("does not handle hex floating constants yet");}
0[xX]{H}*"."{H}+{P}?{FS}?     { errors::die("does not handle hex floating constants yet");}
0[xX]{H}+"."{H}*{P}?{FS}?     { errors::die("does not handle hex floating constants yet");}


L?\"(\\.|[^\\"\n])*\"	{ yylval.string = new std::string(yytext); return(STRING_LITERAL); }

L?\"[^\"\n]*$			{	
							errors::add_err(new error("unterminated string" , true)); 
							yylval.string = new std::string(yytext); 
							return(STRING_LITERAL); 
						}

"..."			{ return(ELLIPSIS); }
">>="			{ return(RIGHT_ASSIGN); }
"<<="			{ return(LEFT_ASSIGN); }
"+="			{ return(ADD_ASSIGN); }
"-="			{ return(SUB_ASSIGN); }
"*="			{ return(MUL_ASSIGN); }
"/="			{ return(DIV_ASSIGN); }
"%="			{ return(MOD_ASSIGN); }
"&="			{ return(AND_ASSIGN); }
"^="			{ return(XOR_ASSIGN); }
"|="			{ return(OR_ASSIGN); }
">>"			{ return(RIGHT_OP); }
"<<"			{ return(LEFT_OP); }
"++"			{ return(INC_OP); }
"--"			{ return(DEC_OP); }
"->"			{ return(PTR_OP); }
"&&"			{ return(AND_OP); }
"||"			{ return(OR_OP); }
"<="			{ return(LE_OP); }
">="			{ return(GE_OP); }
"=="			{ return(EQ_OP); }
"!="			{ return(NE_OP); }
";"				{ return(';'); }
("{"|"<%")		{ return('{'); }
("}"|"%>")		{ return('}'); }
","				{ return(','); }
":"				{ return(':'); }
"="				{ return('='); }
"("				{ return('('); }
")"				{ return(')'); }
("["|"<:")		{ return('['); }
("]"|":>")		{ return(']'); }
"."				{ return('.'); }
"&"				{ return('&'); }
"!"				{ return('!'); }
"~"				{ return('~'); }
"-"				{ return('-'); }
"+"				{ return('+'); }
"*"				{ return('*'); }
"/"				{ return('/'); }
"%"				{ return('%'); }
"<"				{ return('<'); }
">"				{ return('>'); }
"^"				{ return('^'); }
"|"				{ return('|'); }
"?"				{ return('?'); }
[\v\f\t]		{ }
[\n]			{ yycolumn = 1; }
.				{ }

%%


int check_type(const char *s) {
	if(!context::is_member_types_tmp(std::string(s))) return IDENTIFIER;
	else return TYPE_NAME;
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

