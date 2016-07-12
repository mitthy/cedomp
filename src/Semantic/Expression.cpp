/*
 * Expression.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: mitthy
 */
#include "Semantic/Expression.h"
#include "AST/AST.h"
#include <memory>
#include "Scope/Scope.h"
#include "Type/Types.h"
#include "Type/Operations.h"
#include "Exceptions/ExpressionExceptions.h"
#include "Exceptions/TypeExceptions.h"

using namespace Cedomp::AST;

using namespace Cedomp::Exceptions;

ExpressionNode* Cedomp::Semantic::ComputeInteger( long * val )
{
	return new ::IntegerNode(val);
}

ExpressionNode* Cedomp::Semantic::ComputeFloat( double* val )
{
	return new ::FloatNode(val);
}

ExpressionNode* Cedomp::Semantic::ComputeBool( bool * val )
{
	return new ::BoolNode(val);
}

ExpressionNode* Cedomp::Semantic::ComputeID( char * val )
{
	std::string id(val);
	auto& varScope = Cedomp::Scope::Scope::getScope();
	auto& funScope = Cedomp::Scope::FunctionScope::getScope();
	if (funScope.searchScope(id))
	{
		VariableNode* ret = new VariableNode(id, Type::BaseType::TYPEFUNCTION);
		ret->setGenericTypeCode(funScope.searchScope(id)->type);
		return ret;
	}
	else if (varScope.searchScope(id))
	{
		VariableNode* ret = new VariableNode(id,
				varScope.searchScope(id)->type);
		ret->setGenericTypeCode(varScope.searchScope(id)->genericType);
		return ret;
	}
	else
	{
		throw VariableNotDeclaredException(id);
	}

}

ExpressionNode* Cedomp::Semantic::ComputeString( std::string * val )
{
	return new StringNode(val);
}

ExpressionNode* Cedomp::Semantic::ComputeMap(
		std::map<std::string, void*>* val )
{
	return new MapNode(val);
}

ExpressionNode* Cedomp::Semantic::ComputeList( std::vector<void*>* val )
{
	return new ListNode(val);
}

ExpressionNode* Cedomp::Semantic::ComputeIndex( char * id, ExpressionNode* val )
{
	std::string name(id);
	auto& scope = Cedomp::Scope::Scope::getScope();
	auto varSymbol = scope.searchScope(name);
	if (varSymbol)
	{
		auto& operation = Cedomp::Type::Operation::getInstance();
		Cedomp::Type::TypeCode checker;
		operation.getReturnBinaryType(varSymbol->type, "[]", val->getTypeCode(),
				checker);
		if (checker == Cedomp::Type::BaseType::TYPEERROR)
		{
			throw Cedomp::Exceptions::IndexNotSupportedTypeException(name,
					varSymbol->type, val->getTypeCode());
		}
		else
		{
			if (checker != Cedomp::Type::BaseType::TYPEGENERIC)
			{
				varSymbol->genericType = checker;
			}
			if (varSymbol->genericType == Cedomp::Type::BaseType::TYPEGENERIC)
			{
				throw Cedomp::Exceptions::ContainerTypeNotInitialized(name);
			}
			else
			{
				return new IndexNode(varSymbol->genericType, name, val);
			}
		}
	}
	else
	{
		throw VariableNotDeclaredIndexedException(name);
	}
}

void computeBinary( std::string opName, ExpressionNode* left,
		ExpressionNode* right, Cedomp::Type::TypeCode& exprType, bool& coercion,
		Cedomp::Type::TypeCode& genericType )
{
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
	Cedomp::Type::TypeCode genericTypeCode = Cedomp::Type::BaseType::TYPEGENERIC;
	if (checker == Cedomp::Type::BaseType::TYPEERROR)
	{
		//Try coercion
		if (Cedomp::Type::Type::isCompatible(left->getTypeCode(),
				right->getTypeCode()))
		{
			operation.getReturnBinaryType(left->getTypeCode(), opName,
					left->getTypeCode(), checker);
			if (checker == Cedomp::Type::BaseType::TYPEERROR)
			{
				//Try generic type
				if (!operation.getReturnBinaryType(left->getTypeCode(), opName,
						Cedomp::Type::BaseType::TYPEGENERIC, checker))
				{
					throw BinaryOperationNotSupported(opName,
							left->getTypeCode(), right->getTypeCode());
				}
				else
				{
					if (left->getGenericTypeCode()
							== Cedomp::Type::BaseType::TYPEGENERIC)
					{
						genericTypeCode = right->getTypeCode();
					}
					else if (Cedomp::Type::Type::isCompatible(
							left->getGenericTypeCode(), right->getTypeCode()))
					{
						genericTypeCode = left->getGenericTypeCode();
						coercion = true;
					}
					else
					{
						throw IncompatibleTypeException(
								left->getGenericTypeCode(),
								right->getTypeCode());
					}

				}
			}
			else
			{
				//Coercion successful
				coercion = true;
			}
		}
		else
		{
			//Try generic type
			if (!operation.getReturnBinaryType(left->getTypeCode(), opName,
					Cedomp::Type::BaseType::TYPEGENERIC, checker))
			{
				throw BinaryOperationNotSupported(opName, left->getTypeCode(),
						right->getTypeCode());
			}
			else
			{
				if (left->getGenericTypeCode()
						== Cedomp::Type::BaseType::TYPEGENERIC)
				{
					genericTypeCode = right->getTypeCode();
				}
				else if (Cedomp::Type::Type::isCompatible(
						left->getGenericTypeCode(), right->getTypeCode()))
				{
					genericTypeCode = left->getGenericTypeCode();
					coercion = true;
				}
				else
				{
					throw IncompatibleTypeException(left->getGenericTypeCode(),
							right->getTypeCode());
				}
			}
		}
	}
	exprType = checker;
	genericType = genericTypeCode;
}

ExpressionNode* Cedomp::Semantic::ComputeMod( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("mod");
	bool coercion = false;
	Cedomp::Type::TypeCode exprType;
	Cedomp::Type::TypeCode genericType;
	computeBinary(opName, left, right, exprType, coercion, genericType);
	//Return new node here.
	ModNode* ret = new ModNode(exprType, left, right, coercion);
	ret->setGenericTypeCode(genericType);
	return ret;
}

ExpressionNode* Cedomp::Semantic::ComputeAddition( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("+");
	bool coercion = false;
	Cedomp::Type::TypeCode exprType;
	Cedomp::Type::TypeCode genericType;
	computeBinary(opName, left, right, exprType, coercion, genericType);
	//Return new node here.
	AdditionNode* ret = new AdditionNode(exprType, left, right, coercion);
	ret->setGenericTypeCode(genericType);
	return ret;

}

ExpressionNode* Cedomp::Semantic::ComputeSubtraction( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("-");
	bool coercion = false;
	Cedomp::Type::TypeCode exprType;
	Cedomp::Type::TypeCode genericType;
	computeBinary(opName, left, right, exprType, coercion, genericType);
	//Return new node here.
	SubtractionNode* ret = new SubtractionNode(exprType, left, right, coercion);
	ret->setGenericTypeCode(genericType);
	return ret;
}

ExpressionNode* Cedomp::Semantic::ComputeMultiplication( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("*");
	bool coercion = false;
	Cedomp::Type::TypeCode exprType;
	Cedomp::Type::TypeCode genericType;
	computeBinary(opName, left, right, exprType, coercion, genericType);
	//Return new node here.
	MultiplicationNode* ret = new MultiplicationNode(exprType, left, right, coercion);
	ret->setGenericTypeCode(genericType);
	return ret;
}

ExpressionNode* Cedomp::Semantic::ComputeDivision( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("/");
	bool coercion = false;
	Cedomp::Type::TypeCode exprType;
	Cedomp::Type::TypeCode genericType;
	computeBinary(opName, left, right, exprType, coercion, genericType);
	//Return new node here.
	DivisionNode* ret = new DivisionNode(exprType, left, right, coercion);
	ret->setGenericTypeCode(genericType);
	return ret;
}

ExpressionNode* Cedomp::Semantic::ComputeUnaryMinus( ExpressionNode* val )
{
	std::string opName("-");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnUnaryType(val->getTypeCode(), opName, checker);
	if (checker == Cedomp::Type::BaseType::TYPEERROR)
	{
		throw UnaryOperationNotSupported(opName, val->getTypeCode());
	}
	//Return node here
	return new UnaryMinusNode(checker, val);
}

ExpressionNode * Cedomp::Semantic::ComputeGreaterThan( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName(">");
	bool coercion = false;
	Cedomp::Type::TypeCode exprType;
	Cedomp::Type::TypeCode genericType;
	computeBinary(opName, left, right, exprType, coercion, genericType);
	//Return new node here.
	GreaterNode* ret = new GreaterNode(exprType, left, right, coercion);
	ret->setGenericTypeCode(genericType);
	return ret;
}

ExpressionNode * Cedomp::Semantic::ComputeEquals( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName("==");
	bool coercion = false;
	Cedomp::Type::TypeCode exprType;
	Cedomp::Type::TypeCode genericType;
	computeBinary(opName, left, right, exprType, coercion, genericType);
	EqualsNode* ret = new EqualsNode(exprType, left, right, coercion);
	ret->setGenericTypeCode(genericType);
	return ret;
}

ExpressionNode * Cedomp::Semantic::ComputeDifferent( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName("!=");
	bool coercion = false;
	Cedomp::Type::TypeCode exprType;
	Cedomp::Type::TypeCode genericType;
	computeBinary(opName, left, right, exprType, coercion, genericType);
	//Return new node here.
	DifferentNode* ret = new DifferentNode(exprType, left, right, coercion);
	ret->setGenericTypeCode(genericType);
	return ret;
}

ExpressionNode * Cedomp::Semantic::ComputeGreaterEquals( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName(">=");
	bool coercion = false;
	Cedomp::Type::TypeCode exprType;
	Cedomp::Type::TypeCode genericType;
	computeBinary(opName, left, right, exprType, coercion, genericType);
	//Return new node here.
	GreaterEqualNode* ret = new GreaterEqualNode(exprType, left, right, coercion);
	ret->setGenericTypeCode(genericType);
	return ret;
}

ExpressionNode * Cedomp::Semantic::ComputeAnd( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName("and");
	bool coercion = false;
	Cedomp::Type::TypeCode exprType;
	Cedomp::Type::TypeCode genericType;
	computeBinary(opName, left, right, exprType, coercion, genericType);
	//Return new node here.
	AndNode* ret = new AndNode(exprType, left, right, coercion);
	ret->setGenericTypeCode(genericType);
	return ret;
}

ExpressionNode * Cedomp::Semantic::ComputeXor( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName("xor");
	bool coercion = false;
	Cedomp::Type::TypeCode exprType;
	Cedomp::Type::TypeCode genericType;
	computeBinary(opName, left, right, exprType, coercion, genericType);
	//Return new node here.
	XorNode* ret = new XorNode(exprType, left, right, coercion);
	ret->setGenericTypeCode(genericType);
	return ret;
}

ExpressionNode * Cedomp::Semantic::ComputeOr( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName("or");
	bool coercion = false;
	Cedomp::Type::TypeCode exprType;
	Cedomp::Type::TypeCode genericType;
	computeBinary(opName, left, right, exprType, coercion, genericType);
	//Return new node here.
	OrNode* ret = new OrNode(exprType, left, right, coercion);
	ret->setGenericTypeCode(genericType);
	return ret;
}

ExpressionNode * Cedomp::Semantic::ComputeNot( ExpressionNode * val )
{
	std::string opName("not");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnUnaryType(val->getTypeCode(), opName, checker);
	if (checker == Cedomp::Type::BaseType::TYPEERROR)
	{
		throw UnaryOperationNotSupported(opName, val->getTypeCode());
	}
	//Return node here
	return new NotNode(checker, val);
}

ExpressionNode * Cedomp::Semantic::ComputeLessEqual( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName("<=");
	bool coercion = false;
	Cedomp::Type::TypeCode exprType;
	Cedomp::Type::TypeCode genericType;
	computeBinary(opName, left, right, exprType, coercion, genericType);
	LessEqualNode* ret = new LessEqualNode(exprType, left, right, coercion);
	ret->setGenericTypeCode(genericType);
	return ret;
}

ExpressionNode * Cedomp::Semantic::ComputeLess( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName("<");
	bool coercion = false;
	Cedomp::Type::TypeCode exprType;
	Cedomp::Type::TypeCode genericType;
	computeBinary(opName, left, right, exprType, coercion, genericType);
	LessNode* ret = new LessNode(exprType, left, right, coercion);
	ret->setGenericTypeCode(genericType);
	return ret;
}

ExpressionNode * Cedomp::Semantic::ComputeEnclosed( ExpressionNode * val )
{
	return val;
}
