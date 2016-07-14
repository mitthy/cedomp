/*
 * Scope.cpp
 *
 *  Created on: May 13, 2016
 *      Author: mitthy
 */
#include "Scope/Scope.h"
#include "Type/Types.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;
using namespace Cedomp::Scope;
using namespace Cedomp::Type;

variableInfo::variableInfo()
{
	this->type = 0;
	this->globalScope = false;
	this->genericType = BaseType::TYPEGENERIC;
	pointerToFunc = nullptr;

}

/*
 *
 *
 * VAR SCOPE NODE
 *
 *
 */

ScopeNode::ScopeNode( ScopeNode* previous ) :
		previous(previous)
{
}

void ScopeNode::addToScope( const std::string& name, const TypeCode& varType )
{
	variableInfo varInfo;
	varInfo.type = varType;
	variableValMap[name] = varInfo;
}

bool ScopeNode::searchScope( const string& name, variableInfo** outputInfo )
{
	decltype(variableValMap.find(name)) position;
	if ((position = variableValMap.find(name)) == variableValMap.end())
	{
		if (previous)
		{
			return previous->searchScope(name, outputInfo);
		}
		return false;
	}
	else
	{
		*outputInfo = &position->second;

		return true;
	}
}

ScopeNode* ScopeNode::previousNode()
{
	return this->previous;
}

bool ScopeNode::searchCurrentScope( const std::string& varName,
		variableInfo** outputInfo )
{
	auto position = variableValMap.find(varName);
	if (position == variableValMap.end())
	{
		return false;
	}
	*outputInfo = &position->second;
	return true;
}

void ScopeNode::generateScope( ScopeNode** currentScope )
{
	ScopeNode* newScope = new ScopeNode(this);
	this->children.push_back(newScope);
	*currentScope = newScope;
}

void ScopeNode::destroyScope( ScopeNode** currentScope )
{
	if (this->previous != nullptr)
	{
		*currentScope = previous;
	}
}
variableInfo* ScopeNode::searchScope( const std::string& varName )
{
	variableInfo* varInfo = nullptr;
	searchScope(varName, &varInfo);
	return varInfo;
}

ScopeNode::~ScopeNode()
{
	for (auto& child : children)
	{
		delete child;
	}
}

/*
 *
 *
 * VAR SCOPE
 *
 *
 */

Scope& Scope::getScope()
{
	static Scope scope;
	return scope;
}

void Scope::addToScope( const std::string& name, const TypeCode& varType )
{
	tail->addToScope(name, varType);
}

ScopeNode* Scope::getCurrentScope()
{
	return tail;
}

variableInfo* Scope::searchCurrentScope( const string& varName )
{
	variableInfo* ret = nullptr;
	tail->searchCurrentScope(varName, &ret);
	return ret;
}

Scope::~Scope()
{
	delete globalScope;
}

void Scope::generateScope()
{
	tail->generateScope(&tail);
}

variableInfo* Scope::searchScope( const std::string& varName )
{
	variableInfo* varInfo = nullptr;
	tail->searchScope(varName, &varInfo);
	return varInfo;
}

Scope::Scope() :
		globalScope(new ScopeNode(nullptr)), tail(globalScope)
{
}

bool Scope::deleteScope()
{
	tail->destroyScope(&tail);
	return true;
}

/*
 *
 *
 *
 * FUNCTION SCOPE
 *
 *
 */

FunctionScope& FunctionScope::getScope()
{
	static FunctionScope scope;
	return scope;
}

void FunctionScope::addToScope( const std::string& name,
		const Type::TypeCode& varType )
{
	tail->addToScope(name, varType);
}
FunctionScope::~FunctionScope()
{
	delete globalScope;
}
void FunctionScope::generateScope()
{
	tail->generateScope(&tail);
}
functionInfo* FunctionScope::searchScope( const std::string& varName )
{
	return tail->searchScope(varName);
}
functionInfo* FunctionScope::searchCurrentScope( const std::string& varName )
{
	functionInfo* ret = nullptr;
	tail->searchCurrentScope(varName, &ret);
	return ret;
}
bool FunctionScope::deleteScope()
{
	if (tail == globalScope)
	{
		return false;
	}
	tail->destroyScope(&tail);
	return true;
}

FunctionScopeNode* FunctionScope::getCurrentScope()
{
	return tail;
}

FunctionScope::FunctionScope() :
		globalScope(new FunctionScopeNode(nullptr)), tail(globalScope)
{

}

/*
 *
 * FUNCTION SCOPE NODE
 *
 */

FunctionScopeNode::FunctionScopeNode( FunctionScopeNode* previous ): previous(previous)
{
}

bool FunctionScopeNode::searchScope( const std::string& name,
		functionInfo** outputInfo )
{
	if (functionValMap.find(name) == functionValMap.end())
	{
		if (previous == nullptr)
		{
			return false;
		}
		return previous->searchScope(name, outputInfo);
	}
	*outputInfo = &functionValMap[name];
	return true;
}

bool FunctionScopeNode::searchCurrentScope( const std::string& varName,
		functionInfo** outputInfo )
{
	if (functionValMap.find(varName) == functionValMap.end())
	{
		return false;
	}
	*outputInfo = &functionValMap[varName];
	return true;
}

void FunctionScopeNode::addToScope( const std::string& name,
		const Cedomp::Type::TypeCode& varType )
{
	functionInfo info;
	info.type = varType;
	info.name = name;
	functionValMap[name] = info;
}
FunctionScopeNode* FunctionScopeNode::previousNode()
{
	return this->previous;
}

void FunctionScopeNode::generateScope( FunctionScopeNode** curentScope )
{
	FunctionScopeNode* next = new FunctionScopeNode(this);
	this->children.push_back(next);
	*curentScope = next;
}

void FunctionScopeNode::destroyScope( FunctionScopeNode** currentScope )
{
	if (previous != nullptr)
	{
		*currentScope = previous;
	}
}

functionInfo* FunctionScopeNode::searchScope( const std::string& varName )
{
	functionInfo* ret = nullptr;
	searchScope(varName, &ret);
	return ret;
}

FunctionScopeNode::~FunctionScopeNode()
{
	for (auto& child : children)
	{
		delete child;
	}
}
