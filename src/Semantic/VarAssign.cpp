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
#include "Exceptions/ExpressionExceptions.h"
#include "Type/Types.h"
#include <iostream>
#include "Type/Operations.h"
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
		auto& operationCheck = Cedomp::Type::Operation::getInstance();
		Cedomp::Type::TypeCode check;
		operationCheck.getReturnBinaryType(varSymbol->type, "[]",
				index->getTypeCode(), check);
		if (check == Cedomp::Type::BaseType::TYPEERROR)
		{
			throw IndexNotSupportedException(varName);
		}
	}
	else
	{
		//Can't index a variable that was not declared.
		throw VariableNotDeclaredIndexedException(varName);
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
	std::vector<std::unique_ptr<ExpressionNode>> exprRAII;
	for (auto node : (*values))
	{
		exprRAII.push_back(std::unique_ptr<ExpressionNode>(node));
	}
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
				//Check index
				if (!idBeg->index)
				{
					throw IncompatibleTypeException(varSymbol->type,
							(*valBeg)->getTypeCode());
				}
				else
				{
					if (varSymbol->genericType == Type::TYPEGENERIC)
					{
						varSymbol->genericType = (*valBeg)->getTypeCode();
					}
					else
					{
						if (!Cedomp::Type::Type::isCompatible(
								varSymbol->genericType,
								(*valBeg)->getTypeCode()))
						{
							throw IncompatibleTypeException(
									varSymbol->genericType,
									(*valBeg)->getTypeCode());
						}
						else
						{
							if (varSymbol->genericType
									!= (*valBeg)->getTypeCode())
							{
								(*valBeg)->setCoercion(varSymbol->genericType, Cedomp::Type::TYPEGENERIC);
							}
						}
					}
				}
			}
			else
			{
				if (varSymbol->genericType != Type::TYPEGENERIC)
				{
					if (!Cedomp::Type::Type::isCompatible(
							varSymbol->genericType,
							(*valBeg)->getGenericTypeCode()))
					{
						throw IncompatibleTypeException(varSymbol->genericType,
								(*valBeg)->getGenericTypeCode());
					}
					if((*valBeg)->getGenericTypeCode() != varSymbol->genericType)
					{
						(*valBeg)->setCoercion((*valBeg)->getTypeCode(), varSymbol->genericType);
					}
				}
				else
				{

					varSymbol->genericType = (*valBeg)->getGenericTypeCode();
				}
				if (varSymbol->type != (*valBeg)->getTypeCode())
				{
					(*valBeg)->setCoercion(varSymbol->type, Cedomp::Type::TYPEGENERIC);
				}
			}
		}
		else
		{
			VarScope::getScope().addToScope(idBeg->varName,
					(*valBeg)->getTypeCode());
		}
		//If its a function, we should fix the pointer. Ideally, both should be the same and just point
		//to some generic values.
		if((*valBeg)->getTypeCode() == Cedomp::Type::TYPEFUNCTION)
		{
			//Ideally each expression would hold its own value and then it would be a piece of cake.
			//But since we are out of time, this way is better
			auto searchName = (*valBeg)->getName();
			auto functionNode = Cedomp::Scope::FunctionScope::getScope().searchScope(searchName);
			VarScope::getScope().searchScope(idBeg->varName)->pointerToFunc = functionNode;
		}
		//THIS IS NOT EXCEPTION SAFE. SHOULD BE CHANGED ASAP
		if (idBeg->index)
		{
			result->push_back(
					new AssignVariableNode(idBeg->varName, idBeg->index,
							*valBeg));
		}
		else
		{
			result->push_back(new AssignVariableNode(idBeg->varName, *valBeg));
		}
	}
	for (auto& node : exprRAII)
	{
		node.release();
	}
	return result;
}

