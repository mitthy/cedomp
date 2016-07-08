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

using VarScope = Cedomp::Scope::Scope;
using FunScope = Cedomp::Scope::FunctionScope;
using namespace Cedomp::AST;
using namespace Cedomp::Exceptions;

std::vector<std::string>* Cedomp::Semantic::ParseVarNames( std::vector<std::string>* previous,
		std::string varName )
{
	FunScope& fscope = FunScope::getScope();
	if (fscope.searchScope(varName))
	{
		//Can't declare a variable if there is already a function with that name
		throw FunctionAsVariable(varName);
	}
	std::vector<std::string>* result = previous;
	if (!result)
	{
		result = new std::vector<std::string>();
	}
	result->push_back(varName);
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
		const std::vector<std::string>* const ids,
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
		auto varSymbol = VarScope::getScope().searchCurrentScope(*idBeg);
		if(varSymbol)
		{
			if(!Cedomp::Type::Type::isCompatible(varSymbol->type, (*valBeg)->getTypeCode()))
			{
				throw IncompatibleTypeException(varSymbol->type, (*valBeg)->getTypeCode());
			}
		}
		else
		{
			VarScope::getScope().addToScope(*idBeg, (*valBeg)->getTypeCode());
		}
		result->push_back(new AssignVariableNode(*idBeg, *valBeg));
	}
	delete ids;
	delete values;
	return result;
}


