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
#include "Scope/Scope.h"
#include "Exceptions/ExpressionExceptions.h"
#include "Type/Operations.h"
#include "Exceptions/TypeExceptions.h"
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
	functionSymbol->type = Cedomp::Type::TYPEDYNAMIC;
	functionSymbol->genericType = Cedomp::Type::TYPEDYNAMIC;
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

std::vector<ExpressionNode*>* Cedomp::Semantic::PassParameters(
		std::vector<ExpressionNode*>* list, ExpressionNode* next )
{
	std::vector<ExpressionNode*>* ret = list;
	if (ret == nullptr)
	{
		ret = new std::vector<ExpressionNode*>();
	}
	ret->push_back(next);
	return ret;
}

ExpressionNode* Cedomp::Semantic::CheckParameters( char* id )
{
	std::string funcName(id);
	auto val = Cedomp::Scope::FunctionScope::getScope().searchScope(funcName);
	if (val)
	{
		if (val->argInfo.size())
		{
			throw Cedomp::Exceptions::WrongNumberOfArguments(
					val->argInfo.size(), 0);
		}
		ExpressionNode* ret = new FunctionCallNode(val->name, val->type);
		ret->setGenericTypeCode(Cedomp::Type::TYPEDYNAMIC);
		return ret;

	}
	else
	{
		auto varNode = Cedomp::Scope::Scope::getScope().searchScope(funcName);
		if (!varNode)
		{
			throw Cedomp::Exceptions::VariableNotDeclaredException(funcName);
		}
		Cedomp::Type::TypeCode checker;
		if (!Cedomp::Type::Operation::getInstance().getReturnUnaryType(
				varNode->type, "()", checker))
		{
			throw Cedomp::Exceptions::UnaryOperationNotSupported("()",
					varNode->type);
		}
		val = varNode->pointerToFunc;
		if (!val)
		{
			std::cerr << "BUG" << std::endl;
			std::exit(-1);
		}
		if (val->argInfo.size())
		{
			throw Cedomp::Exceptions::WrongNumberOfArguments(
					val->argInfo.size(), 0);
		}
		ExpressionNode* ret = new FunctionCallNode(val->name, val->type);
		ret->setGenericTypeCode(Cedomp::Type::TYPEDYNAMIC);
		return ret;
	}

}

ExpressionNode* Cedomp::Semantic::CheckParameters( char* id,
		std::vector<ExpressionNode*>* params )
{

	std::string funcName(id);
	auto val = Cedomp::Scope::FunctionScope::getScope().searchScope(funcName);
	if (val)
	{
		if (val->argInfo.size() != params->size())
		{
			int sz = params->size();
			for (auto val : (*params))
			{
				delete val;
			}
			delete params;
			throw Cedomp::Exceptions::WrongNumberOfArguments(
					val->argInfo.size(), sz);
		}
		auto argBeg = val->argInfo.begin();
		auto argEnd = val->argInfo.end();
		auto paramBeg = params->begin();
		auto paramEnd = params->end();
		Cedomp::Type::TypeCode type1;
		Cedomp::Type::TypeCode type2;
		bool throwExcp = false;
		for (; argBeg != argEnd || paramBeg != paramEnd; ++argBeg, ++paramBeg)
		{
			auto argNode = (*argBeg);
			auto paramNode = (*paramBeg);

			if (Cedomp::Type::Type::isCompatible(argNode->getTypeCode(),
					paramNode->getTypeCode()))
			{
				if (!Cedomp::Type::Type::isCompatible(
						argNode->getGenericTypeCode(),
						paramNode->getGenericTypeCode()))
				{
					type1 = argNode->getGenericTypeCode();
					type2 = paramNode->getGenericTypeCode();
					throwExcp = true;
					break;
				}
				else
				{
					Cedomp::Type::TypeCode coercionType =
							Cedomp::Type::TYPEGENERIC;
					Cedomp::Type::TypeCode coercionGenericType =
							Cedomp::Type::TYPEGENERIC;
					if (argNode->getTypeCode() != paramNode->getTypeCode())
					{
						coercionType = argNode->getTypeCode();
					}
					if (argNode->getGenericTypeCode()
							!= paramNode->getGenericTypeCode())
					{
						coercionGenericType = argNode->getGenericTypeCode();
					}
					if (coercionType != Cedomp::Type::BaseType::TYPEDYNAMIC
							&& coercionGenericType
									!= Cedomp::Type::BaseType::TYPEDYNAMIC)
					{
						paramNode->setCoercion(coercionType,
								coercionGenericType);
					}

				}
			}
			else
			{
				type1 = argNode->getTypeCode();
				type2 = paramNode->getTypeCode();
				throwExcp = true;
				break;
			}
		}
		if (throwExcp)
		{
			for (auto val : (*params))
			{
				delete val;
			}
			delete params;
			throw Cedomp::Exceptions::IncompatibleTypeException(type1, type2);
		}
		ExpressionNode* ret = new FunctionCallNode(val->name, val->type,
				params);
		ret->setGenericTypeCode(Cedomp::Type::TYPEDYNAMIC);
		return ret;

	}
	else
	{
		auto varNode = Cedomp::Scope::Scope::getScope().searchScope(funcName);
		if (!varNode)
		{
			throw Cedomp::Exceptions::VariableNotDeclaredException(funcName);
		}
		Cedomp::Type::TypeCode checker;
		if (!Cedomp::Type::Operation::getInstance().getReturnUnaryType(
				varNode->type, "()", checker))
		{
			throw Cedomp::Exceptions::UnaryOperationNotSupported("()",
					varNode->type);
		}
		val = varNode->pointerToFunc;
		if (!val)
		{
			std::cerr << "BUG" << std::endl;
			std::exit(-1);
		}
		if (val->argInfo.size() != params->size())
		{
			int sz = params->size();
			for (auto val : (*params))
			{
				delete val;
			}
			delete params;
			throw Cedomp::Exceptions::WrongNumberOfArguments(
					val->argInfo.size(), sz);
		}
		auto argBeg = val->argInfo.begin();
		auto argEnd = val->argInfo.end();
		auto paramBeg = params->begin();
		auto paramEnd = params->end();
		Cedomp::Type::TypeCode type1;
		Cedomp::Type::TypeCode type2;
		bool throwExcp = false;
		for (; argBeg != argEnd || paramBeg != paramEnd; ++argBeg, ++paramBeg)
		{
			auto argNode = (*argBeg);
			auto paramNode = (*paramBeg);
			if (Cedomp::Type::Type::isCompatible(argNode->getTypeCode(),
					paramNode->getTypeCode()))
			{
				if (!Cedomp::Type::Type::isCompatible(
						argNode->getGenericTypeCode(),
						paramNode->getGenericTypeCode()))
				{
					type1 = argNode->getGenericTypeCode();
					type2 = paramNode->getGenericTypeCode();
					throwExcp = true;
					break;
				}
				else
				{
					Cedomp::Type::TypeCode coercionType =
							Cedomp::Type::TYPEGENERIC;
					Cedomp::Type::TypeCode coercionGenericType =
							Cedomp::Type::TYPEGENERIC;
					if (argNode->getTypeCode() != paramNode->getTypeCode())
					{
						coercionType = argNode->getTypeCode();
					}
					if (argNode->getGenericTypeCode()
							!= paramNode->getGenericTypeCode())
					{
						coercionGenericType = argNode->getGenericTypeCode();
					}
					paramNode->setCoercion(coercionType, coercionGenericType);
				}
			}
			else
			{
				type1 = argNode->getTypeCode();
				type2 = paramNode->getTypeCode();
				throwExcp = true;
				break;
			}
		}
		if (throwExcp)
		{
			for (auto val : (*params))
			{
				delete val;
			}
			delete params;
			throw Cedomp::Exceptions::IncompatibleTypeException(type1, type2);
		}
		ExpressionNode* ret = new FunctionCallNode(val->name, val->type,
				params);
		ret->setGenericTypeCode(Cedomp::Type::TYPEDYNAMIC);
		return ret;
	}
}
