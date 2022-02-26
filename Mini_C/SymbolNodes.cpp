#pragma once

#include <iostream>
#include "SymbolNodes.h"
#include "SymbolTable.h"

// Accessing the constructor of CompileUnit is done by calling the its parent constructor
// Access is achieved by :: and :(Initialization first and then implementations inside the body{}. Example CNUMBER).
CCompileUnit::CCompileUnit() : STNode(NodeType::NT_COMPILEUNIT) {}
CCompileUnit::~CCompileUnit() {}

void CCompileUnit::Visit_SyntaxTreePrinter(ofstream* dotFile, STNode* parent) {
	list<STNode*>::iterator it;

	// If node CompileUnit has not parent..
	if (parent == nullptr) {
		(*dotFile) << "digraph G{ \n";
		for (it = m_children->begin(); it != m_children->end(); it++) {
			(*it)->Visit_SyntaxTreePrinter(dotFile, this);
		}

		(*dotFile) << "}";
		dotFile->close();
	}
	// If node CompileUnit has parent..
	else {
		STNode::Visit_SyntaxTreePrinter(dotFile, this);
	}
}

CStatements::CStatements() : STNode(NodeType::NT_STATEMENTS) {}
CStatements::~CStatements() {}

int CStatements::Visit_Eval() 
{
	list<STNode*>::iterator it;

	for (it = m_children->begin(); it != m_children->end(); it++)
	{
		(*it)->Visit_Eval();

		if (ms_breakVisit) {
			break;
		}
		if (ms_continueVisit) {
			break;
		}
	}
	return 0;
}

CStatement::CStatement() : STNode(NodeType::NT_STATEMENT) {}
CStatement::~CStatement() {}

int CStatement::Visit_Eval()
{
	/* Because there are two cases and in one of them we have a child we should check it before taking action..*/
	list<STNode*> ::iterator it;

	if (m_children->size() != 0)
	{
		it = m_children->begin();
		cout << "Result : " << (*it)->Visit_Eval() << endl;
	}

	return 0;
}

CCompoundStatement::CCompoundStatement() : STNode(NT_COMPOUND_STATEMENT) {}
CCompoundStatement::~CCompoundStatement() {}

CAddition::CAddition() : STNode(NodeType::NT_EXPRESSION_ADDITION) {}
CAddition::~CAddition() {}

int CAddition::Visit_Eval()
{
	// We set up an iterator to run its children. It shows to the first element of the list with the children..
	list<STNode*> ::iterator it = m_children->begin();
	// Result of the first children..
	int result = (*it)->Visit_Eval();
	// Increase the iterator to point to the next child..
	advance(it, 1);
	// Addition of the new child and the previous one..
	result += (*it)->Visit_Eval();

	// Return result to parent node..
	return result;
}

CSubtraction::CSubtraction() : STNode(NodeType::NT_EXPRESSION_SUBTRACTION) {}
CSubtraction::~CSubtraction() {}

int CSubtraction::Visit_Eval()
{
	list<STNode*> ::iterator it = m_children->begin();
	int result = (*it)->Visit_Eval();
	advance(it, 1);
	result -= (*it)->Visit_Eval();

	return result;
}

CMultiplication::CMultiplication() : STNode(NodeType::NT_EXPRESSION_MULTIPLICATION) {}
CMultiplication::~CMultiplication() {}

int CMultiplication::Visit_Eval()
{
	list<STNode*> ::iterator it = m_children->begin();
	int result = (*it)->Visit_Eval();
	advance(it, 1);
	result *= (*it)->Visit_Eval();

	return result;
}

CDivision::CDivision() : STNode(NodeType::NT_EXPRESSION_DIVISION) {}
CDivision::~CDivision() {}

int CDivision::Visit_Eval()
{
	list<STNode*> ::iterator it = m_children->begin();
	int result = (*it)->Visit_Eval();
	advance(it, 1);
	result /= (*it)->Visit_Eval();

	return result;
}

CNUMBER::CNUMBER(int number) : STNode(NodeType::NT_EXPRESSION_NUMBER) {
	m_number = number;
	m_graphvizLabel.append("_" + std::to_string(getNumber()));
}
CNUMBER::~CNUMBER() {}

int CNUMBER::Visit_Eval() {
	return m_number;
}

CIDENTIFIER::CIDENTIFIER(char* text) : STNode(NodeType::NT_EXPRESSION_IDENTIFIER)
{
	m_name = (string)text;
	m_name_c = new char[m_name.length() + 1];
	strcpy_s(m_name_c, m_name.length() + 1, text);
	m_number = 0;
	m_root = nullptr;
	m_graphvizLabel.append("_" + m_name);
}
CIDENTIFIER::~CIDENTIFIER() { delete m_name_c; }

int CIDENTIFIER::Visit_Eval() {
	return m_number;
}

CAssignment::CAssignment() : STNode(NodeType::NT_EXPRESSION_ASSIGNMENT) {}
CAssignment::~CAssignment() {}

int CAssignment::Visit_Eval()
{
	list<STNode*>::iterator it = m_children->begin();
	CIDENTIFIER* id = dynamic_cast<CIDENTIFIER*>(*it);
	advance(it, 1);
	id->m_number = (*it)->Visit_Eval();
	cout << id->m_name << "= " << id->m_number << endl;

	return id->m_number;
}

CLessExpression::CLessExpression() : STNode(NT_LESS_EXPRESSION) {}
CLessExpression::~CLessExpression() {}

int CLessExpression::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	int left = (*it)->Visit_Eval();
	advance(it, 1);
	int right = (*it)->Visit_Eval();

	return left < right;
}

CGreaterExpression::CGreaterExpression() : STNode(NT_GREATER_EXPRESSION) {}
CGreaterExpression::~CGreaterExpression() {}

int CGreaterExpression::Visit_Eval() {
	return STNode::Visit_Eval();
}

CLessEqualExpression::CLessEqualExpression() : STNode(NT_LESS_EQUAL_EXPRESSION) {}
CLessEqualExpression::~CLessEqualExpression() {}

int CLessEqualExpression::Visit_Eval() {
	return STNode::Visit_Eval();
}

CGreaterEqualExpression::CGreaterEqualExpression() : STNode(NT_GREATER_EQUAL_EXPRESSION) {}
CGreaterEqualExpression::~CGreaterEqualExpression() {}

int CGreaterEqualExpression::Visit_Eval() {
	return STNode::Visit_Eval();
}

CEqualExpression::CEqualExpression() : STNode(NT_EQUAL_EXPRESSION) {}
CEqualExpression::~CEqualExpression() {}

int CEqualExpression::Visit_Eval() {
	return STNode::Visit_Eval();
}

CNotEqualExpression::CNotEqualExpression() : STNode(NT_NOT_EQUAL_EXPRESSION) {}
CNotEqualExpression::~CNotEqualExpression() {}

int CNotEqualExpression::Visit_Eval() {
	return STNode::Visit_Eval();
}

CANDExpression::CANDExpression() : STNode(NT_AND_EXPRESSION) {}
CANDExpression::~CANDExpression() {}

int CANDExpression::Visit_Eval() {
	return STNode::Visit_Eval();
}

CORExpression::CORExpression() : STNode(NT_OR_EXPRESSION) {}
CORExpression::~CORExpression() {}

int CORExpression::Visit_Eval() {
	return STNode::Visit_Eval();
}

CNOTExpression::CNOTExpression() : STNode(NT_NOT_EXPRESSION) {}
CNOTExpression::~CNOTExpression() {}

int CNOTExpression::Visit_Eval() {
	return STNode::Visit_Eval();
}

CIfStatement::CIfStatement() : STNode(NT_STATEMENT_IF) {}
CIfStatement::~CIfStatement() {}

int CIfStatement::Visit_Eval() 
{
	STNode* condition = GetChild(0);
	STNode* true_body = GetChild(1);
	STNode* false_body;

	if (condition->Visit_Eval()) {
		true_body->Visit_Eval();
	}
	else if (m_children->size() > 2)
	{
		false_body = GetChild(2);
		false_body->Visit_Eval();
	}

	return 0;
}

CWhileStatement::CWhileStatement() : STNode(NT_STATEMENT_WHILE) {}
CWhileStatement::~CWhileStatement() {}

int CWhileStatement::Visit_Eval() 
{
	STNode* condition = GetChild(0);
	STNode* body = GetChild(1);

	while (condition->Visit_Eval()) 
	{
		body->Visit_Eval();
		if (ms_breakVisit)
			break;
		if (ms_continueVisit)
			ms_continueVisit = false;
	}
	ms_breakVisit = false;
	return 0;
}

CBreakStatement::CBreakStatement() : STNode(NT_STATEMENT_BREAK) {}
CBreakStatement::~CBreakStatement() {}

int CBreakStatement::Visit_Eval() {
	ms_breakVisit = true;
	return 0;
}

CContinueStatement::CContinueStatement() : STNode(NT_STATEMENT_CONTINUE) {}
CContinueStatement::~CContinueStatement() {}

int CContinueStatement::Visit_Eval() {
	ms_continueVisit = true;
	return 0;
}

CFormalArgs::CFormalArgs() : STNode(NT_FORMAL_ARGS) {}
CFormalArgs::~CFormalArgs() {}

CActualArgs::CActualArgs() : STNode(NT_ACTUAL_ARGS) {}
CActualArgs::~CActualArgs() {}

CFunctionCallExpression::CFunctionCallExpression() : STNode(NT_FUNCTION_CALL_EXPRESSION) {}
CFunctionCallExpression::~CFunctionCallExpression() {}

int CFunctionCallExpression::Visit_Eval() {
	//1. get access to the function identifier object to get m_root
	//*m_root gives acces to function code
	char* f_name = ((CIDENTIFIER*)GetChild(0))->m_name_c;
	CIDENTIFIER* f_id = (CIDENTIFIER*)g_symbolTable.getIdentifier(f_name);

	CFunctionDefinition* fun_def = (CFunctionDefinition*)f_id->m_root;

	//2. store actuall args in a list
	CActualArgs* f_a_args = (CActualArgs*)GetChild(1);
	list<STNode*>* actual_args = new list<STNode*>;
	getActualArguments(f_a_args, actual_args);

	//3. store formal args in a list
	CFormalArgs* f_f_args = (CFormalArgs*)fun_def->GetChild(1);
	list<STNode*>* formal_args = new list<STNode*>;
	getFormalArguments(f_f_args, formal_args);

	//4. map actuall args to formal args
	list<STNode*>::iterator formal_it;
	list<STNode*>::iterator actual_it;
	for (formal_it = formal_args->begin(), actual_it = actual_args->begin();
		formal_it != formal_args->end(); formal_it++, actual_it++) {

		dynamic_cast<CIDENTIFIER*>(*formal_it)->m_number = (*actual_it)->Visit_Eval();
	}

	fun_def->GetChild(2)->Visit_Eval();

	return STNode::ms_returned_value;
}

int getActualArguments(CActualArgs* root, list<STNode*>* actual_args) {
	if (dynamic_cast<CActualArgs*>(root->GetChild(0)) != nullptr) {
		CActualArgs* next = dynamic_cast<CActualArgs*>(root->GetChild(0));
		getActualArguments(next, actual_args);
		actual_args->push_back(root->GetChild(1));
	}
	else {
		actual_args->push_back(root->GetChild(0));
	}
	return actual_args->size();
}

int getFormalArguments(CFormalArgs* root, list<STNode*>* formal_args) {
	if (dynamic_cast<CFormalArgs*>(root->GetChild(0)) != nullptr) {
		CFormalArgs* next = dynamic_cast<CFormalArgs*>(root->GetChild(0));
		getFormalArguments(next, formal_args);
		formal_args->push_back(root->GetChild(1));
	}
	else {
		formal_args->push_back(root->GetChild(0));
	}
	return formal_args->size();
}

CFunctionDefinition::CFunctionDefinition() :STNode(NT_FUNCTION_DEFINITION) {}
CFunctionDefinition::~CFunctionDefinition() {}

CRETURNStatement::CRETURNStatement() : STNode(NT_STATEMENT_RETURN) {}
CRETURNStatement::~CRETURNStatement() {}

int CRETURNStatement::Visit_Eval()
{
	STNode* expr = GetChild(0);
	ms_returned_value = expr->Visit_Eval();
	return ms_returned_value;
}
