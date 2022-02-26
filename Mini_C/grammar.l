
%option noyywrap

%{
#include <iostream>
#include <stdlib.h>

#include "grammar.tab.h"
#define YY_DECL int yylex(yy::parser::semantic_type *yylval, yy::parser::location_type *yylloc)
# define YY_USER_ACTION yylloc->columns(yyleng);

typedef yy::parser::token::yytokentype token;

#include "SymbolNodes.h"
#include "SymbolTable.h"

%}

%%

%{
// start where previous token ended
yylloc->step ();
%}

","	{ return ','; }
";"	{ return ';'; }
"+"	{ return '+'; }
"-"	{ return '-'; }
"*"	{ return '*'; }
"/"	{ return '/'; }
")"	{ return ')'; }
"("	{ return '('; }
"="	{ return '='; }
"}"	{ return '}'; }
"{"	{ return '{'; }

"<"	{ return token::L; }
">"	{ return token::G; }
"<="	{ return token::LE; }
">="	{ return token::GE; }
"=="	{ return token::EQ; }
"!="	{ return token::NE; }
"&&"	{ return token::GE; }
"||"	{ return token::EQ; }
"!"	{ return token::NOT; }

"if"		{ return token::IF; }
"else"		{ return token::ELSE; }
"while"		{ return token::WHILE; }
"break"		{ return token::BREAK; }
"continue"	{ return token::CONTINUE; }
"return"	{ return token::RETURN; }
"function"	{ return token::FUNCTION; }


"0"|([1-9][0-9]*)	{
	yylval->node = new CNUMBER(atoi(yytext));
	return token::NUMBER;
}

[a-zA-Z][a-zA-Z0-9_]*	{
	yylval->node = g_symbolTable.getIdentifier(yytext);
	return token::IDENTIFIER;
}

[ \t]		{ yylloc->step (); }
[\r\n]		{ yylloc->lines(1);}

%%