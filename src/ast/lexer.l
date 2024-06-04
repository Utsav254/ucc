%option noyywrap
%option nounput
%{	
	//from: https://www.quut.com/c/ANSI-C-grammar-l-1999.html
	extern "C" int fileno(FILE *stream);

	#include "parser.tab.hpp"
	#include <stdio.h>

	void count(void);
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

"auto"			{ count(); return(AUTO); }
"break"			{ count(); return(BREAK); }
"case"			{ count(); return(CASE); }
"char"			{ count(); return(CHAR); }
"const"			{ count(); return(CONST); }
"continue"		{ count(); return(CONTINUE); }
"default"		{ count(); return(DEFAULT); }
"do"			{ count(); return(DO); }
"double"		{ count(); return(DOUBLE); }
"else"			{ count(); return(ELSE); }
"enum"			{ count(); return(ENUM); }
"extern"		{ count(); return(EXTERN); }
"float"			{ count(); return(FLOAT); }
"for"			{ count(); return(FOR); }
"goto"			{ count(); return(GOTO); }
"if"			{ count(); return(IF); }
"inline"		{ count(); return(INLINE); }
"int"			{ count(); return(INT); }
"long"			{ count(); return(LONG); }
"register"		{ count(); return(REGISTER); }
"restrict"		{ count(); return(RESTRICT); }
"return"		{ count(); return(RETURN); }
"short"			{ count(); return(SHORT); }
"signed"		{ count(); return(SIGNED); }
"sizeof"		{ count(); return(SIZEOF); }
"static"		{ count(); return(STATIC); }
"struct"		{ count(); return(STRUCT); }
"switch"		{ count(); return(SWITCH); }
"typedef"		{ count(); return(TYPEDEF); }
"union"			{ count(); return(UNION); }
"unsigned"		{ count(); return(UNSIGNED); }
"void"			{ count(); return(VOID); }
"volatile"		{ count(); return(VOLATILE); }
"while"			{ count(); return(WHILE); }

{L}({L}|{D})*		{yylval.string = new std::string(yytext) ; count(); return(check_type()); }

0[xX]{H}+{IS}?		{count(); yylval.number_int = (int)strtol(yytext , NULL , 0); return(INT_CONSTANT); }
0[0-7]*{IS}?		{count(); yylval.number_int = (int)strtol(yytext , NULL , 0); return(INT_CONSTANT); }
[1-9]{D}*{IS}?		{count(); yylval.number_int = (int)strtol(yytext , NULL , 0); return(INT_CONSTANT); }
L?'(\\.|[^\\'\n])+'	{count(); yylval.letter_char = extract_char_value(yytext); return(CHAR_CONSTANT); }

{D}+{E}{FS}?		{count(); yylval.number_float = strtod(yytext, NULL); return(FLOAT_CONSTANT); }
{D}*"."{D}+{E}?{FS}?	{count(); yylval.number_float = strtod(yytext , NULL); return(FLOAT_CONSTANT); }
{D}+"."{D}*{E}?{FS}?	{count(); yylval.number_float = strtod(yytext , NULL); return(FLOAT_CONSTANT); }

0[xX]{H}+{P}{FS}?	{ count(); die("does not handle hex floating constants yet" , errcode::SYNTAX);}
0[xX]{H}*"."{H}+{P}?{FS}?     { count(); die("does not handle hex floating constants yet" , errcode::SYNTAX);}
0[xX]{H}+"."{H}*{P}?{FS}?     { count(); die("does not handle hex floating constants yet" , errcode::SYNTAX);}


L?\"(\\.|[^\\"\n])*\"	{ count(); /*yet to handle string literals...*/ return(STRING_LITERAL); }

"..."			{ count(); return(ELLIPSIS); }
">>="			{ count(); return(RIGHT_ASSIGN); }
"<<="			{ count(); return(LEFT_ASSIGN); }
"+="			{ count(); return(ADD_ASSIGN); }
"-="			{ count(); return(SUB_ASSIGN); }
"*="			{ count(); return(MUL_ASSIGN); }
"/="			{ count(); return(DIV_ASSIGN); }
"%="			{ count(); return(MOD_ASSIGN); }
"&="			{ count(); return(AND_ASSIGN); }
"^="			{ count(); return(XOR_ASSIGN); }
"|="			{ count(); return(OR_ASSIGN); }
">>"			{ count(); return(RIGHT_OP); }
"<<"			{ count(); return(LEFT_OP); }
"++"			{ count(); return(INC_OP); }
"--"			{ count(); return(DEC_OP); }
"->"			{ count(); return(PTR_OP); }
"&&"			{ count(); return(AND_OP); }
"||"			{ count(); return(OR_OP); }
"<="			{ count(); return(LE_OP); }
">="			{ count(); return(GE_OP); }
"=="			{ count(); return(EQ_OP); }
"!="			{ count(); return(NE_OP); }
";"				{ count(); return(';'); }
("{"|"<%")		{ count(); return('{'); }
("}"|"%>")		{ count(); return('}'); }
","				{ count(); return(','); }
":"				{ count(); return(':'); }
"="				{ count(); return('='); }
"("				{ count(); return('('); }
")"				{ count(); return(')'); }
("["|"<:")		{ count(); return('['); }
("]"|":>")		{ count(); return(']'); }
"."				{ count(); return('.'); }
"&"				{ count(); return('&'); }
"!"				{ count(); return('!'); }
"~"				{ count(); return('~'); }
"-"				{ count(); return('-'); }
"+"				{ count(); return('+'); }
"*"				{ count(); return('*'); }
"/"				{ count(); return('/'); }
"%"				{ count(); return('%'); }
"<"				{ count(); return('<'); }
">"				{ count(); return('>'); }
"^"				{ count(); return('^'); }
"|"				{ count(); return('|'); }
"?"				{ count(); return('?'); }

[ \t\v\n\f]		{ count(); }
.				{  }

%%


int err_column = 0;
std::string err_string;

void count(void) {
	int i;
	for (i = 0; yytext[i] != '\0'; i++) {

		if (yytext[i] == '\n') err_column = 0;
		else if (yytext[i] == '\t') err_column += 4 - (err_column % 4);
		else err_column++;
	}

	err_string = yytext;	
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


