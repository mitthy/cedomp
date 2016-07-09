/*
 * VarAssign.cpp
 *
 *  Created on: Jul 7, 2016
 *      Author: mitthy
 */

#include "Scope/Scope.h"
#include "Semantic/VarAssign.h"
#include <string>
#include <vector>
#include "AST/AST.h"
#include "Exceptions/VarAssignExceptions.h"
#include "Exceptions/TypeExceptions.h"
#include "Type/Types.h"
#include <iostream>

using VarScope = Cedomp::Scope::Scope;
using FunScope = Cedomp::Scope::FunctionScope;
using Cedomp::Semantic::VarNameIndex;
using namespace Cedomp::AST;
using namespace Cedomp::Exceptions;

std::vector<VarNameIndex>* Cedomp::Semantic::ParseVarNames(
		std::vector<VarNameIndex>* previous, std::string varName )
{
	FunScope& fscope = FunScope::getScope();
	if (fscope.searchScope(varName))
	{
		//Can't declare a variable if there is already a function with that name
		throw FunctionAsVariable(varName);
	}
	std::vector<VarNameIndex>* result = previous;
	if (!result)
	{
		result = new std::vector<VarNameIndex>();
	}
	VarNameIndex varAssgn;
	varAssgn.index = nullptr;
	varAssgn.varName = varName;
	result->push_back(varAssgn);
	return result;
}

std::vector<VarNameIndex>* Cedomp::Semantic::ParseVarNames(
		std::vector<VarNameIndex>* previous, std::string varName,
		AST::ExpressionNode* index )
{
	FunScope& fscope = FunScope::getScope();
	if (fscope.searchScope(varName))
	{
		//Can't declare a variable if there is already a function with that name
		throw FunctionAsVariable(varName);
	}
	auto varSymbol = VarScope::getScope().searchScope(varName);
	if (varSymbol)
	{
		//If it is a base type of the language:
		if (Cedomp::Type::Type::isBaseType(varSymbol->type))
		{
			//Check if it supports indexing
			if (varSymbol->type != Cedomp::Type::BaseType::TYPEMAP
					&& varSymbol->type != Cedomp::Type::BaseType::TYPELIST)
			{
				throw IndexNotSupportedException(varName);
			}
		}
	}
	else
	{
		//Can't index a variable that was not declared.
		throw VariableNotDeclaredException(varName);
	}
	std::vector<VarNameIndex>* result = previous;
	if (!result)
	{
		result = new std::vector<VarNameIndex>();
	}
	VarNameIndex varAssgn;
	varAssgn.index = index;
	varAssgn.varName = varName;
	result->push_back(varAssgn);
	return result;
}

std::vector<ExpressionNode*>* Cedomp::Semantic::ParseAssignExpressions(
		std::vector<ExpressionNode*>* previous, ExpressionNode* expr )
{
	std::vector<ExpressionNode*>* result = previous;
	if (!result)
	{
		result = new std::vector<ExpressionNode*>();
	}
	result->push_back(expr);
	return result;
}

std::vector<AssignVariableNode*>* Cedomp::Semantic::AssignVariable(
		const std::vector<VarNameIndex>* const ids,
		const std::vector<ExpressionNode*>* const values )
{
	if (ids->size() != values->size())
	{
		throw WrongVarNumberException(ids->size(), values->size());
	}
	auto idEnd = ids->end();
	auto valEnd = values->end();
	std::vector<AssignVariableNode*>* result = new std::vector<
			AssignVariableNode*>();
	auto idBeg = ids->begin();
	auto valBeg = values->begin();
	for (; idBeg != idEnd || valBeg != valEnd; ++idBeg, ++valBeg)
	{
		auto varSymbol = VarScope::getScope().searchCurrentScope(idBeg->varName);
		if (varSymbol)
		{
			if (!Cedomp::Type::Type::isCompatible(varSymbol->type,
					(*valBeg)->getTypeCode()))
			{
				throw IncompatibleTypeException(varSymbol->type,
						(*valBeg)->getTypeCode());
			}
		}
		else
		{
			VarScope::getScope().addToScope(idBeg->varName, (*valBeg)->getTypeCode());
		}
		//Change to support indexing
		result->push_back(new AssignVariableNode(idBeg->varName, *valBeg));
	}
	delete ids;
	delete values;
	return result;
}

