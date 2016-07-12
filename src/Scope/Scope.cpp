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

Scope& Scope::getScope()
{
	static Scope scope;
	return scope;
}

FunctionScope& FunctionScope::getScope()
{
	static FunctionScope scope;
	return scope;
}

variableInfo::variableInfo()
{
	this->type = 0;
	this->globalScope = false;
	this->genericType = BaseType::TYPEGENERIC;

}

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

Scope::Scope() :
		globalScope(new ScopeNode(nullptr)), tail(globalScope)
{
}

ScopeNode* Scope::getCurrentScope()
{
	return tail;
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
	for(auto child : children)
	{
		delete child;
	}
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

bool Scope::deleteScope()
{
	tail->destroyScope(&tail);
}

FunctionScope::FunctionScope() :
		functionValMap(std::map<std::string, functionInfo>())
{
}

void FunctionScope::addToScope( const std::string& name,
		const TypeCode& varType, std::vector<AST::VariableNode*> args )
{
	functionInfo entry;
	entry.defined = false;
	entry.type = varType;
	entry.argInfo = std::vector<variableInfo>();
	for (auto& var : args)
	{
		variableInfo varInfo;
		//TODO
		//varInfo.isArray = var->isArray();
		//varInfo.type = var->getType();
		//varInfo.arrSize = var->arrSize();
		varInfo.globalScope = false;
		entry.argInfo.push_back(varInfo);
	}
	functionValMap[name] = entry;
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

variableInfo* Scope::searchCurrentScope( const string& varName )
{
	variableInfo* ret = nullptr;
	tail->searchCurrentScope(varName, &ret);
	return ret;
}

functionInfo* FunctionScope::searchScope( const std::string& funcName )
{
	auto position = functionValMap.find(funcName);
	if (position == functionValMap.end())
	{
		return nullptr;
	}
	return &position->second;
}

void Scope::addToScope( const std::string& name, const TypeCode& varType )
{
	tail->addToScope(name, varType);
}

std::map<std::string, functionInfo>::iterator FunctionScope::begin()
{
	return this->functionValMap.begin();
}

std::map<std::string, functionInfo>::iterator FunctionScope::end()
{
	return this->functionValMap.end();
}

FunctionScope::~FunctionScope()
{

}
