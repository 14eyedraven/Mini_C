#pragma once

/* Creation of the Abstract Parent Class of Syntax Tree */

#include <list>
#include <string>
#include <fstream>

using namespace std;

/* Each member is a separate integer code for each type of node we want to create in the syntax tree.*/
typedef enum nodeType {
	NT_COMPILEUNIT, NT_STATEMENTS, NT_STATEMENT,
	NT_EXPRESSION_NUMBER, NT_EXPRESSION_IDENTIFIER,
	NT_EXPRESSION_ADDITION, NT_EXPRESSION_SUBTRACTION,
	NT_EXPRESSION_MULTIPLICATION, NT_EXPRESSION_DIVISION,
	NT_EXPRESSION_ASSIGNMENT, NT_COMPOUND_STATEMENT,
	NT_STATEMENT_IF, NT_STATEMENT_ELSE,
	NT_STATEMENT_WHILE, NT_STATEMENT_BREAK, NT_STATEMENT_CONTINUE,
	NT_FORMAL_ARGS, NT_ACTUAL_ARGS,
	NT_FUNCTION_CALL_EXPRESSION, NT_FUNCTION_DEFINITION, NT_STATEMENT_RETURN,

	NT_LESS_EXPRESSION, NT_GREATER_EXPRESSION,
	NT_LESS_EQUAL_EXPRESSION, NT_GREATER_EQUAL_EXPRESSION,
	NT_EQUAL_EXPRESSION, NT_NOT_EQUAL_EXPRESSION,
	NT_AND_EXPRESSION, NT_OR_EXPRESSION, NT_NOT_EXPRESSION

}NodeType;

class STNode abstract{
public:
	// Query Methods. 
	// These methods are needed to print our syntax tree after crossing it.

	// Returns node type (enum declaration..)
	NodeType GetNodeType();
	// Returns label tag
	string GetGraphvizLabel();
	// Returns a child
	STNode* GetChild(int index);
	// Returns a parent
	STNode* GetParent(int index = 0);

	// Modifier class, add new child to current	node.
	// It will also put it in the end of our list.
	void AddChild(STNode* node);

	// Crossing tree.
	virtual void Visit_SyntaxTreePrinter(ofstream* dotFile, STNode* parent);

	// Go to the syntax tree to calculate the values of the expressions given at the input..
	virtual int Visit_Eval();


protected:

	// Constructor and Destructor
	STNode(NodeType type);
	virtual ~STNode();

	// Type of node
	NodeType m_nodeType;
	// label of node in the graphviz generated file
	string m_graphvizLabel;
	// serial number of the node, distinct for each node.
	int m_serial;
	// serial counter
	static int m_serialCounter;
	// children nodes list
	list <STNode*>* m_children;
	// parent nodes list
	list <STNode*>* m_parents;


	static int ms_returned_value;
	static bool ms_breakVisit;
	static bool ms_continueVisit;
};

extern STNode* g_root;