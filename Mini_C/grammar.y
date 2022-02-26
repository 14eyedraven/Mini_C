
%{
#include <iostream>
#include <stdlib.h>

#include "grammar.tab.h"
extern int yylex(yy::parser::semantic_type *yylval, yy::parser::location_type *yylloc);
%}

%language "C++"

%locations

%initial-action {
// Filename for locations here
@$.begin.filename = @$.end.filename = new std::string("test.txt");
}

%start compileUnit

%code requires {
	#include "STNode.h"
	#include "SymbolNodes.h"
}

%union {
	STNode *node;
}

%token <node> NUMBER IDENTIFIER
%token <node> IF ELSE WHILE
%token <node> FUNCTION
%token <node> BREAK CONTINUE RETURN 

%type <node> compileUnit statements statement compound_statement
%type <node> expression if_statement while_statement
%type <node> function_definition formal_args actual_args

%verbose

%nonassoc PARTIALIFRULE
%nonassoc ELSE

%right '='
%left OR
%left AND
%nonassoc L G LE GE EQ NE
%left '+' '-'
%left '*' '/'
%nonassoc NOT

%%

compileUnit	: statement {
							$$ = new CCompileUnit();
							g_root = $$;
							$$->AddChild($1);
						}
						| compileUnit statement {
							$$ = new CCompileUnit();
							g_root = $$;
							$$->AddChild($1);
							$$->AddChild($2);
						}
						| function_definition {
							$$ = new CCompileUnit();
							g_root = $$;
							$$->AddChild($1);
						}
						| compileUnit function_definition {
							$$ = new CCompileUnit();
							g_root = $$;
							$$->AddChild($1);
							$$->AddChild($2);
						}
						;

function_definition	: FUNCTION IDENTIFIER '(' formal_args ')' compound_statement {
									$$ = new CFunctionDefinition();
									((CIDENTIFIER*) $2)->m_root = $$;
									$$->AddChild($2); //0
									$$->AddChild($4); //1
									$$->AddChild($6); //2
								}
								| FUNCTION IDENTIFIER '(' ')' compound_statement {
									$$ = new CFunctionDefinition();
									((CIDENTIFIER*) $2)->m_root = $$;
									$$->AddChild($2);
									$$->AddChild($5);
								}
								;

formal_args	: IDENTIFIER {
						$$ = new CFormalArgs();
						$$->AddChild($1);
					}
					| formal_args ',' IDENTIFIER {
						$$ = new CFormalArgs();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					;

compound_statement	: '{' '}'		{
										$$ = new CCompoundStatement();
									}
									| '{' statements '}' {
										$$ = new CCompoundStatement();
										$$->AddChild($2);
									}
									;

statements	: statement {
						$$ = new CStatements();
						$$->AddChild($1);
					}
					| statements statement {
						$$ = new CStatements();
						$$->AddChild($1);
						$$->AddChild($2);
					}
					;

statement	: expression ';' {
					$$ = $1;
				}
				| if_statement {
					$$ = $1;
				}
				| while_statement {
					$$ = $1;
				}
				| BREAK ';' {
					$$ = new CBreakStatement();
				}
				| CONTINUE ';' {
					$$ = new CContinueStatement();
				}
				| RETURN expression ';' {
					$$ = new CRETURNStatement();
					$$->AddChild($2);
				}
				| ';'  {
					$$ = new CStatement();
				}
				;

if_statement	: IF '(' expression ')' statement %prec PARTIALIFRULE {
						$$ = new CIfStatement();
						$$->AddChild($3);
						$$->AddChild($5);
					}
					| IF '(' expression ')' statement ELSE statement {
						$$ = new CIfStatement();
						$$->AddChild($3);
						$$->AddChild($5);
						//if it has 3 childs means there is else statement at 3rd child
						$$->AddChild($7);
					}
					;

while_statement	: WHILE '(' expression ')' compound_statement {
								$$ = new CWhileStatement();
								$$->AddChild($3);
								$$->AddChild($5);
							}
							| WHILE '(' expression ')' statement {
								$$ = new CWhileStatement();
								$$->AddChild($3);
								$$->AddChild($5);
							}
							;

expression		: NUMBER	{ $$ = $1; }		
					| IDENTIFIER { $$ = $1; }	
					| IDENTIFIER '=' expression {
						//assignment
						$$ = new CAssignment();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					| IDENTIFIER '(' ')' {
						//function call with no arguments
						$$ = new CFunctionCallExpression();
						$$->AddChild($1);
					}
					| IDENTIFIER '(' actual_args ')' {
						//function call with arguments
						$$ = new CFunctionCallExpression();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					| expression '+' expression	{
						$$ = new CAddition();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					| expression '-' expression	{
						$$ = new CSubtraction();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					| expression '*' expression	{
						$$ = new CMultiplication();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					| expression '/' expression	{
						$$ = new CDivision();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					| '(' expression ')'	{ $$ = $2; }



					| expression L expression	{
						$$ = new CLessExpression();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					| expression G expression	{
						$$ = new CGreaterExpression();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					| expression LE expression	{
						$$ = new CLessEqualExpression();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					| expression GE expression	{
						$$ = new CGreaterEqualExpression();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					| expression EQ expression	{
						$$ = new CEqualExpression();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					| expression NE expression	{
						$$ = new CNotEqualExpression();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					| expression AND expression	{
						$$ = new CANDExpression();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					| expression OR expression	{
						$$ = new CORExpression();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					| NOT expression	{
						$$ = new CNOTExpression();
						$$->AddChild($2);
					}
					;

actual_args	: expression {
						$$ = new CActualArgs();
						$$->AddChild($1);
					}
					| actual_args ',' expression {
						$$ = new CActualArgs();
						$$->AddChild($1);
						$$->AddChild($3);
					}
					;

%%

void yy::parser::error(const location_type& loc, const std::string& msg) {
	std::cerr << "error at " << loc << ": " << msg << std::endl;
}