#pragma once

#include <map>
#include <string>

#include "STNode.h"
#include "SymbolNodes.h"

using namespace std;

class SymbolTable {
public:
	map<string, STNode*> m_symbolTable;
	STNode* getIdentifier(char* name);
};

extern SymbolTable g_symbolTable;


