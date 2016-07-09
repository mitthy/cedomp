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
#include <memory>

/*
 * We use unique_ptr inside functions to avoid leaks.
 */

using VarScope = Cedomp::Scope::Scope;
using FunScope = Cedomp::Scope::FunctionScope;
using Cedomp::Semantic::VarNameIndex;
using namespace Cedomp::AST;
using namespace Cedomp::Exceptions;

std::vector<VarNameIndex>* Cedomp::Semantic::ParseVarNames(
		std::vector<VarNameIndex>* previous, std::string varName )
{
	std::unique_ptr<std::vector<VarNameIndex>> previousRAII(previous);
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
	previousRAII.release();
	return result;
}

std::vector<VarNameIndex>* Cedomp::Semantic::ParseVarNames(
		std::vector<VarNameIndex>* previous, std::string varName,
		AST::ExpressionNode* index )
{
	std::unique_ptr<std::vector<VarNameIndex>> previousRAII(previous);
	std::unique_ptr<AST::ExpressionNode> indexRAII(index);
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
	previousRAII.release();
	indexRAII.release();
	return result;
}

std::vector<ExpressionNode*>* Cedomp::Semantic::ParseAssignExpressions(
		std::vector<ExpressionNode*>* previous, ExpressionNode* expr )
{
	std::unique_ptr<std::vector<ExpressionNode*>> previousRAII(previous);
	std::unique_ptr<ExpressionNode> exprRAII(expr);
	std::vector<ExpressionNode*>* result = previous;
	if (!result)
	{
		result = new std::vector<ExpressionNode*>();
	}
	result->push_back(expr);
	previousRAII.release();
	exprRAII.release();
	return result;
}

std::vector<AssignVariableNode*>* Cedomp::Semantic::AssignVariable(
		std::vector<VarNameIndex>* ids, std::vector<ExpressionNode*>* values )
{
	std::unique_ptr<std::vector<VarNameIndex>> idsRAII(ids);
	std::unique_ptr<std::vector<ExpressionNode*>> valuesRAII(values);
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
		auto varSymbol = VarScope::getScope().searchCurrentScope(
				idBeg->varName);
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
			VarScope::getScope().addToScope(idBeg->varName,
					(*valBeg)->getTypeCode());
		}
		//Change to support indexing
		result->push_back(new AssignVariableNode(idBeg->varName, *valBeg));
	}
	return result;
}

