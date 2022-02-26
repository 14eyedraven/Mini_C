#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#include "grammar.tab.h"
#include "STNode.h"

extern FILE* yyin;

int main(int argc, char* argv[])
{
	fopen_s(&yyin, argv[1], "r");
	yy::parser* p = new yy::parser();
	p->parse();

	// Output File.
	ofstream* f = new ofstream("test.dot", ofstream::out);
	g_root->Visit_SyntaxTreePrinter(f, nullptr);
	system("dot -Tgif test.dot -o test.gif");

	g_root->Visit_Eval();

	return 0;
}

