%option noyywrap
%option nounput
%{	
	//from: https://www.quut.com/c/ANSI-C-grammar-l-1999.html
	extern "C" int fileno(FILE *stream);

	#include "parser.tab.hpp"
	#include <stdio.h>
	#include <string.h>
	#include <string>

	int errlineno = 0;
	std::string errpadding;

	void count(const char *s);
	int check_type(void);
	char extract_char_value(const char *text);
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

"auto"			{ count(yytext); return(AUTO); }
"break"			{ count(yytext); return(BREAK); }
"case"			{ count(yytext); return(CASE); }
"char"			{ count(yytext); return(CHAR); }
"const"			{ count(yytext); return(CONST); }
"continue"		{ count(yytext); return(CONTINUE); }
"default"		{ count(yytext); return(DEFAULT); }
"do"			{ count(yytext); return(DO); }
"double"		{ count(yytext); return(DOUBLE); }
"else"			{ count(yytext); return(ELSE); }
"enum"			{ count(yytext); return(ENUM); }
"extern"		{ count(yytext); return(EXTERN); }
"float"			{ count(yytext); return(FLOAT); }
"for"			{ count(yytext); return(FOR); }
"goto"			{ count(yytext); return(GOTO); }
"if"			{ count(yytext); return(IF); }
"inline"		{ count(yytext); return(INLINE); }
"int"			{ count(yytext); return(INT); }
"long"			{ count(yytext); return(LONG); }
"register"		{ count(yytext); return(REGISTER); }
"restrict"		{ count(yytext); return(RESTRICT); }
"return"		{ count(yytext); return(RETURN); }
"short"			{ count(yytext); return(SHORT); }
"signed"		{ count(yytext); return(SIGNED); }
"sizeof"		{ count(yytext); return(SIZEOF); }
"static"		{ count(yytext); return(STATIC); }
"struct"		{ count(yytext); return(STRUCT); }
"switch"		{ count(yytext); return(SWITCH); }
"typedef"		{ count(yytext); return(TYPEDEF); }
"union"			{ count(yytext); return(UNION); }
"unsigned"		{ count(yytext); return(UNSIGNED); }
"void"			{ count(yytext); return(VOID); }
"volatile"		{ count(yytext); return(VOLATILE); }
"while"			{ count(yytext); return(WHILE); }

{L}({L}|{D})*		{count(yytext); yylval.string = new std::string(yytext); return(check_type()); }

0[xX]{H}+{IS}?		{count(yytext); yylval.number_int = (int)strtol(yytext , NULL , 0); return(INT_CONSTANT); }
0[0-7]*{IS}?		{count(yytext); yylval.number_int = (int)strtol(yytext , NULL , 0); return(INT_CONSTANT); }
[1-9]{D}*{IS}?		{count(yytext); yylval.number_int = (int)strtol(yytext , NULL , 0); return(INT_CONSTANT); }
L?'(\\.|[^\\'\n])+'	{count(yytext); yylval.letter_char = extract_char_value(yytext); return(CHAR_CONSTANT); }

{D}+{E}{FS}?		{count(yytext); yylval.number_float = strtod(yytext, NULL); return(FLOAT_CONSTANT); }
{D}*"."{D}+{E}?{FS}?	{count(yytext); yylval.number_float = strtod(yytext , NULL); return(FLOAT_CONSTANT); }
{D}+"."{D}*{E}?{FS}?	{count(yytext); yylval.number_float = strtod(yytext , NULL); return(FLOAT_CONSTANT); }

0[xX]{H}+{P}{FS}?	{ count(yytext); die("does not handle hex floating constants yet" , errcode::SYNTAX);}
0[xX]{H}*"."{H}+{P}?{FS}?     { count(yytext); die("does not handle hex floating constants yet" , errcode::SYNTAX);}
0[xX]{H}+"."{H}*{P}?{FS}?     { count(yytext); die("does not handle hex floating constants yet" , errcode::SYNTAX);}


\"(\\.|[^\\"\n])*\"	{ count(yytext); /*yet to handle string literals...*/ return(STRING_LITERAL); }

"..."			{ count(yytext); return(ELLIPSIS); }
">>="			{ count(yytext); return(RIGHT_ASSIGN); }
"<<="			{ count(yytext); return(LEFT_ASSIGN); }
"+="			{ count(yytext); return(ADD_ASSIGN); }
"-="			{ count(yytext); return(SUB_ASSIGN); }
"*="			{ count(yytext); return(MUL_ASSIGN); }
"/="			{ count(yytext); return(DIV_ASSIGN); }
"%="			{ count(yytext); return(MOD_ASSIGN); }
"&="			{ count(yytext); return(AND_ASSIGN); }
"^="			{ count(yytext); return(XOR_ASSIGN); }
"|="			{ count(yytext); return(OR_ASSIGN); }
">>"			{ count(yytext); return(RIGHT_OP); }
"<<"			{ count(yytext); return(LEFT_OP); }
"++"			{ count(yytext); return(INC_OP); }
"--"			{ count(yytext); return(DEC_OP); }
"->"			{ count(yytext); return(PTR_OP); }
"&&"			{ count(yytext); return(AND_OP); }
"||"			{ count(yytext); return(OR_OP); }
"<="			{ count(yytext); return(LE_OP); }
">="			{ count(yytext); return(GE_OP); }
"=="			{ count(yytext); return(EQ_OP); }
"!="			{ count(yytext); return(NE_OP); }
";"				{ count(yytext); return(';'); }
("{"|"<%")		{ count(yytext); return('{'); }
("}"|"%>")		{ count(yytext); return('}'); }
","				{ count(yytext); return(','); }
":"				{ count(yytext); return(':'); }
"="				{ count(yytext); return('='); }
"("				{ count(yytext); return('('); }
")"				{ count(yytext); return(')'); }
("["|"<:")		{ count(yytext); return('['); }
("]"|":>")		{ count(yytext); return(']'); }
"."				{ count(yytext); return('.'); }
"&"				{ count(yytext); return('&'); }
"!"				{ count(yytext); return('!'); }
"~"				{ count(yytext); return('~'); }
"-"				{ count(yytext); return('-'); }
"+"				{ count(yytext); return('+'); }
"*"				{ count(yytext); return('*'); }
"/"				{ count(yytext); return('/'); }
"%"				{ count(yytext); return('%'); }
"<"				{ count(yytext); return('<'); }
">"				{ count(yytext); return('>'); }
"^"				{ count(yytext); return('^'); }
"|"				{ count(yytext); return('|'); }
"?"				{ count(yytext); return('?'); }
"\n"			{ errlineno++; errpadding = "";}
"\t"			{ errpadding += "\t";}
[\v\f]			{ count(yytext); }
.				{ count(yytext); }

%%


void count(const char *s) {
	int len = (int)strlen(s);
	for (int i = 0 ; i < len ; i++){
		errpadding += " ";
	}
}

int check_type(void) {

	/*used for checking if an identifier is a potential type a list of types must be mainted and chechked against...

	used for wierd things like enumerate or typedefinitons

	of-course these types also have a scope...
	*/

	return IDENTIFIER;
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


