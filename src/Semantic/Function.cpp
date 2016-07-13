/*
 * Function.cpp
 *
 *  Created on: Jul 12, 2016
 *      Author: mitthy
 */
#include "AST/AST.h"
#include "Semantic/Function.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include "Semantic/Utility.h"
#include <set>
#include "Exceptions/FunctionExceptions.h"
#include <algorithm>
using namespace Cedomp::AST;
using Cedomp::Semantic::FunctionInfo;

struct ReturnType
{
	Cedomp::Type::TypeCode returnType;
	Cedomp::Type::TypeCode genericType;
	bool operator<( const ReturnType& rhs ) const
	{
		if (std::min(returnType, genericType)
				< std::min(rhs.returnType, rhs.genericType))
		{
			return true;
		}

		else if (std::min(rhs.returnType, rhs.genericType)
				< std::min(returnType, genericType))
		{
			return false;
		}

		else
		{
			return (std::max(returnType, genericType)
					< std::max(rhs.returnType, rhs.genericType));
		}

	}
};

FunctionNode* Cedomp::Semantic::CreateFunction( FunctionInfo* functionInfo,
		BlockNode* bodyInfo )
{
	auto& funcScope = Cedomp::Scope::FunctionScope::getScope();
	auto functionSymbol = funcScope.searchScope(functionInfo->name);
	functionSymbol->defined = true;
	if (functionInfo->args)
	{
		for (auto& element : (*(functionInfo->args)))
		{
			std::shared_ptr<ExpressionNode> toAdd(element);
			functionSymbol->argInfo.push_back(toAdd);
		}
	}
	std::vector<ExpressionNode*> returnValues;
	bodyInfo->searchReturnValue(returnValues);
	bool searchForReturnType = true;
	for (auto& node : returnValues)
	{
		if (node->getTypeCode() == Cedomp::Type::TYPEDYNAMIC)
		{
			searchForReturnType = false;
			functionSymbol->type = Cedomp::Type::TYPEDYNAMIC;
			functionSymbol->genericType = Cedomp::Type::TYPEDYNAMIC;
		}
	}
	if (searchForReturnType)
	{
		ReturnType retType;
		retType.returnType = Cedomp::Type::TYPEDYNAMIC;
		retType.genericType = Cedomp::Type::TYPEDYNAMIC;
		//Now we should figure out a uniform return type for the function
		std::set<ReturnType> returnTypeCodes;

		for (auto& node : returnValues)
		{
			auto nodeTypeCode = node->getTypeCode();
			auto nodeGenericTypeCode = node->getGenericTypeCode();
			ReturnType value;
			value.genericType = nodeGenericTypeCode;
			value.returnType = nodeTypeCode;
			returnTypeCodes.insert(value);
		}
		std::set<ReturnType> candidateTypes;
		for (auto element : returnTypeCodes)
		{
			bool candidate = true;
			for (auto elementToCompare : returnTypeCodes)
			{

				if (!Cedomp::Type::Type::isCompatible(element.returnType,
						elementToCompare.returnType)
						|| !Cedomp::Type::Type::isCompatible(
								element.genericType,
								elementToCompare.genericType))
				{
					candidate = false;
					break;
				}
			}
			if (candidate)
			{
				candidateTypes.insert(element);
			}
		}
		if (candidateTypes.empty())
		{
			functionSymbol->type = Cedomp::Type::TYPEDYNAMIC;
			functionSymbol->genericType = Cedomp::Type::TYPEDYNAMIC;
		}
		else if (candidateTypes.size() > 1)
		{
			for (auto& node : returnValues)
			{
				ReturnType checker;
				checker.returnType = node->getTypeCode();
				checker.genericType = node->getGenericTypeCode();
				if (candidateTypes.find(checker) != candidateTypes.end())
				{
					functionSymbol->type = checker.returnType;
					functionSymbol->genericType = checker.genericType;
					break;
				}
			}
		}
		else
		{
			auto val = (*candidateTypes.begin());
			functionSymbol->genericType = val.genericType;
			functionSymbol->type = val.returnType;
		}

	}
	return new FunctionNode(functionInfo->name, functionInfo->args,
			functionSymbol->type, functionSymbol->genericType, bodyInfo);
}

std::vector<ExpressionNode*>* Cedomp::Semantic::ParseArgList(
		std::vector<ExpressionNode*>* previous, ExpressionNode* expr )
{
	std::vector<ExpressionNode*>* result = previous;
	if (!result)
	{
		result = new std::vector<ExpressionNode*>();
	}
//Add id to scope
	result->push_back(expr);
	return result;
}

FunctionInfo* Cedomp::Semantic::AddFunctionToScope( char* name,
		std::vector<AST::ExpressionNode*>* args )
{
	std::string id(name);
	if (Cedomp::Semantic::getContext() == Cedomp::Semantic::IF
			|| Cedomp::Semantic::getContext() == Cedomp::Semantic::WHILE)
	{
		throw Cedomp::Exceptions::FunctionContextException();
	}
	auto& scope = Cedomp::Scope::FunctionScope::getScope();
	auto& varScope = Cedomp::Scope::Scope::getScope();
	if (varScope.searchScope(id))
	{
		throw Cedomp::Exceptions::VariableAsFunction(id);
	}
	if (scope.searchScope(id))
	{
		throw Cedomp::Exceptions::RedeclarationOfFunction(id);
	}
	scope.addToScope(id, Cedomp::Type::TYPEDYNAMIC);
	FunctionInfo* ret = new FunctionInfo();
	ret->args = args;
	ret->name = id;
	return ret;
}

FunctionInfo* Cedomp::Semantic::AddFunctionToScope( char* name )
{
	std::string id(name);
	if (Cedomp::Semantic::ContainsContext(Cedomp::Semantic::IF)
			|| Cedomp::Semantic::ContainsContext(Cedomp::Semantic::WHILE))
	{
		throw Cedomp::Exceptions::FunctionContextException();
	}
	auto& scope = Cedomp::Scope::FunctionScope::getScope();
	auto& varScope = Cedomp::Scope::Scope::getScope();
	if (varScope.searchScope(id))
	{
		throw Cedomp::Exceptions::VariableAsFunction(id);
	}
//Is this ok?
	scope.addToScope(id, Cedomp::Type::TYPEDYNAMIC);
	FunctionInfo* ret = new FunctionInfo();
	ret->args = nullptr;
	ret->name = id;
	return ret;

}

BlockNode* Cedomp::Semantic::ParseFunctionBody( BlockNode* body )
{
	std::vector<ExpressionNode*> returnValues;
	body->searchReturnValue(returnValues);
	if (returnValues.empty())
	{
		long* val = new long;
		*val = 0;
		ExpressionNode* newRet = new IntegerNode(val);
		ReturnNode* returnNode = new ReturnNode(newRet);
		body->addNode(returnNode);
	}
	return body;
}

ReturnNode* Cedomp::Semantic::CheckReturnStatement( ExpressionNode* expr )
{
	if (!Cedomp::Semantic::ContainsContext(Cedomp::Semantic::Context::FUNCTION))
	{
		throw Cedomp::Exceptions::ReturnOutsideFunction();
	}
	return new ReturnNode(expr);
}
