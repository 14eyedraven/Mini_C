#pragma once

/*Subsidiary Classes..*/

#include "STNode.h"

/* Classes representing nodes of the syntactic tree..*/
					// Inheritance
class CCompileUnit : public STNode {
public:
	CCompileUnit();
	virtual ~CCompileUnit();
	void Visit_SyntaxTreePrinter(ofstream* dotFile, STNode* parent) override;
};

class CStatements : public STNode {
public:
	CStatements();
	virtual ~CStatements();
	int Visit_Eval() override;
};

class CStatement : public STNode {
public:
	CStatement();
	virtual ~CStatement();

	int Visit_Eval() override;
};

class CCompoundStatement : public STNode {
public:
	CCompoundStatement();
	virtual ~CCompoundStatement();
};

/* Single Responsibility Priciple(SRP): Each class must have at most one responsibility in program operation.
That's why we create a different class for each operation. By creating a class called expression and having to handle all this
operation we violate this principle. */

class CAddition : public STNode {
public:
	CAddition();
	virtual ~CAddition();

	int Visit_Eval() override;
};

class CSubtraction : public STNode {
public:
	CSubtraction();
	virtual ~CSubtraction();

	int Visit_Eval() override;
};

class CMultiplication : public STNode {
public:
	CMultiplication();
	virtual ~CMultiplication();

	int Visit_Eval() override;
};

class CDivision : public STNode {
public:
	CDivision();
	virtual ~CDivision();

	int Visit_Eval() override;
};

class CNUMBER : public STNode {
public:

	CNUMBER(int);
	virtual ~CNUMBER();
	int getNumber() { return m_number; }

	int Visit_Eval() override;

protected:
	int m_number;
};

class CIDENTIFIER : public STNode {
public:
	int m_number;
	string m_name;
	char* m_name_c;
	STNode* m_root;

	CIDENTIFIER(char* text);
	virtual ~CIDENTIFIER();

	int Visit_Eval() override;
};

class CAssignment : public STNode {
public:
	CAssignment();
	virtual ~CAssignment();

	int Visit_Eval() override;
};

class CLessExpression : public STNode {
public:
	CLessExpression();
	virtual ~CLessExpression();
	int Visit_Eval() override;
};

class CGreaterExpression : public STNode {
public:
	CGreaterExpression();
	virtual ~CGreaterExpression();
	int Visit_Eval() override;
};

class CLessEqualExpression : public STNode {
public:
	CLessEqualExpression();
	virtual ~CLessEqualExpression();
	int Visit_Eval() override;
};

class CGreaterEqualExpression : public STNode {
public:
	CGreaterEqualExpression();
	virtual ~CGreaterEqualExpression();
	int Visit_Eval() override;
};

class CEqualExpression : public STNode {
public:
	CEqualExpression();
	virtual ~CEqualExpression();
	int Visit_Eval() override;
};

class CNotEqualExpression : public STNode {
public:
	CNotEqualExpression();
	virtual ~CNotEqualExpression();
	int Visit_Eval() override;
};

class CANDExpression : public STNode {
public:
	CANDExpression();
	virtual ~CANDExpression();
	int Visit_Eval() override;
};

class CORExpression : public STNode {
public:
	CORExpression();
	virtual ~CORExpression();
	int Visit_Eval() override;
};

class CNOTExpression : public STNode {
public:
	CNOTExpression();
	virtual ~CNOTExpression();
	int Visit_Eval() override;
};

class CIfStatement : public STNode {
public:
	CIfStatement();
	virtual ~CIfStatement();
	int Visit_Eval() override;
};

class CWhileStatement : public STNode {
public:
	CWhileStatement();
	virtual ~CWhileStatement();
	int Visit_Eval() override;
};

class CBreakStatement : public STNode {
public:
	CBreakStatement();
	virtual ~CBreakStatement();
	int Visit_Eval() override;
};

class CContinueStatement : public STNode {
public:
	CContinueStatement();
	virtual ~CContinueStatement();
	int Visit_Eval() override;
};

class CFormalArgs : public STNode {
public:
	CFormalArgs();
	virtual ~CFormalArgs();
};

class CActualArgs : public STNode {
public:
	CActualArgs();
	virtual ~CActualArgs();
};

class CFunctionCallExpression : public STNode {
public:
	CFunctionCallExpression();
	virtual ~CFunctionCallExpression();
	int Visit_Eval() override;
};

int getFormalArguments(CFormalArgs* root, list<STNode*>* formal_args);
int getActualArguments(CActualArgs* root, list<STNode*>* actual_args);

class CFunctionDefinition : public STNode {
public:
	CFunctionDefinition();
	virtual ~CFunctionDefinition();
};

class CRETURNStatement : public STNode {
public:
	CRETURNStatement();
	virtual ~CRETURNStatement();
	int Visit_Eval() override;
};
