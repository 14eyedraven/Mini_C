#pragma once

#include "STNode.h"

STNode* g_root = nullptr;

// Access m_serialCounter (::)
int STNode::m_serialCounter = 0;

int STNode::ms_returned_value = 0;
bool STNode::ms_breakVisit = false;
bool STNode::ms_continueVisit = false;

// Names for all types of nodes, position should be equal to the value of its corresponding field(Addressing).
const char* g_nodeTypeLabels[] = {
	"COMPILEUNIT", "STATEMENTS", "STATEMENT",
	"NUMBER", "IDENTIFIER", "ADDITION", "SUBTRACTION",
	"MULTIPLICATION", "DIVISION", 
	"ASSIGNMENT", "COMPOUND STATEMENT",
	"IF", "ELSE",
	"WHILE", "BREAK", "CONTINUE",
	"FORMAL ARGS", "ACTUAL ARGS",
	"FUNCTION CALL", "FUNCTION DEFINITION", "RETURN",

	"LESS", "GREATER",
	"LESS EQUAL", "GREATER EQUAL",
	"EQUAL", "NOT EQUAL",
	"AND", "OR", "NOT"
};

// Initialization (Constructor)
STNode::STNode(NodeType type)
{
	m_nodeType = type;
	m_serial = m_serialCounter++; // Attribution via the static variable m_serialCounter.
	m_children = new list<STNode*>;
	m_parents = new list<STNode*>;
	//Initialization node name.
	m_graphvizLabel = _strdup(g_nodeTypeLabels[m_nodeType]);
	// Add its serial number.
	m_graphvizLabel.append("_" + std::to_string(m_serial));
}

// Destructor
STNode::~STNode() {

	// Delete every node by crossing the syntax tree.
	list<STNode*>::iterator it;
	for (it = m_children->begin(); it != m_children->end(); it++) {
		delete* it;
	}

	delete m_children;
	delete m_parents;
}

// Add node in the end of children's list.
void STNode::AddChild(STNode* node) {
	m_children->push_back(node);
	// Update parent (connectivity).
	node->m_parents->push_back(this);
}

// 
STNode* STNode::GetChild(int index) {
	list<STNode*>::iterator it = m_children->begin();
	advance(it, index);
	return *it;
}

STNode* STNode::GetParent(int index) {
	list<STNode*>::iterator it = m_parents->begin();
	advance(it, index);
	return *it;
}

void STNode::Visit_SyntaxTreePrinter(ofstream* dotFile, STNode* parent) {
	list<STNode*>::iterator it;

	// Printing the edge from father to the current node.
	(*dotFile) << "\"" << parent->GetGraphvizLabel() << "\"->\"" << GetGraphvizLabel() << "\";\n";

	// Recursive crossing.
	for (it = m_children->begin(); it != m_children->end(); it++) {
		(*it)->Visit_SyntaxTreePrinter(dotFile, this);
	}
}

int STNode::Visit_Eval() {
	list<STNode*>::iterator it;

	for (it = m_children->begin(); it != m_children->end(); it++) {
		(*it)->Visit_Eval();
	}
	
	return 0;
}

NodeType STNode::GetNodeType() {
	return m_nodeType;
}

string STNode::GetGraphvizLabel() {
	return m_graphvizLabel;
}