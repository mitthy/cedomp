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
		return new VariableNode(id, Type::BaseType::TYPEFUNCTION);
	}
	else if (varScope.searchScope(id))
	{
		return new VariableNode(id, varScope.searchScope(id)->type);
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

ExpressionNode* Cedomp::Semantic::ComputeMod( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("mod");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
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
				throw BinaryOperationNotSupported(opName, left->getTypeCode(),
						right->getTypeCode());
			}
			//Coercion successful
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
}

ExpressionNode* Cedomp::Semantic::ComputeAddition( ExpressionNode* left,
		ExpressionNode* right )
{
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), "+",
			right->getTypeCode(), checker);
	if (checker == Cedomp::Type::BaseType::TYPEERROR)
	{
		//Try coercion
		if (Cedomp::Type::Type::isCompatible(left->getTypeCode(),
				right->getTypeCode()))
		{
			operation.getReturnBinaryType(left->getTypeCode(), "+",
					left->getTypeCode(), checker);
			if (checker == Cedomp::Type::BaseType::TYPEERROR)
			{
				throw BinaryOperationNotSupported("+", left->getTypeCode(),
						right->getTypeCode());
			}
			//Coercion successful
		}
		else
		{
			throw BinaryOperationNotSupported("+", left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.

}

ExpressionNode* Cedomp::Semantic::ComputeSubtraction( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("-");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
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
				throw BinaryOperationNotSupported(opName, left->getTypeCode(),
						right->getTypeCode());
			}
			//Coercion successful
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
}

ExpressionNode* Cedomp::Semantic::ComputeMultiplication( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("*");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
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
				throw BinaryOperationNotSupported(opName, left->getTypeCode(),
						right->getTypeCode());
			}
			//Coercion successful
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
}

ExpressionNode* Cedomp::Semantic::ComputeDivision( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("/");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
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
				throw BinaryOperationNotSupported(opName, left->getTypeCode(),
						right->getTypeCode());
			}
			//Coercion successful
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
}

ExpressionNode* Cedomp::Semantic::ComputeUnaryMinus( ::ExpressionNode* val )
{

}

ExpressionNode* Cedomp::Semantic::ComputeGreaterThan( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName(">");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
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
				throw BinaryOperationNotSupported(opName, left->getTypeCode(),
						right->getTypeCode());
			}
			//Coercion successful
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
}

ExpressionNode* Cedomp::Semantic::ComputeEquals( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("==");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
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
				throw BinaryOperationNotSupported(opName, left->getTypeCode(),
						right->getTypeCode());
			}
			//Coercion successful
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
}

ExpressionNode* Cedomp::Semantic::ComputeDifferent( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("!=");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
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
				throw BinaryOperationNotSupported(opName, left->getTypeCode(),
						right->getTypeCode());
			}
			//Coercion successful
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
}

ExpressionNode* Cedomp::Semantic::ComputeGreaterEquals( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName(">=");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
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
				throw BinaryOperationNotSupported(opName, left->getTypeCode(),
						right->getTypeCode());
			}
			//Coercion successful
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
}

ExpressionNode* Cedomp::Semantic::ComputeAnd( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("and");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
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
				throw BinaryOperationNotSupported(opName, left->getTypeCode(),
						right->getTypeCode());
			}
			//Coercion successful
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
}

ExpressionNode* Cedomp::Semantic::ComputeXor( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("xor");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
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
				throw BinaryOperationNotSupported(opName, left->getTypeCode(),
						right->getTypeCode());
			}
			//Coercion successful
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
}

ExpressionNode* Cedomp::Semantic::ComputeOr( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("or");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
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
				throw BinaryOperationNotSupported(opName, left->getTypeCode(),
						right->getTypeCode());
			}
			//Coercion successful
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
}

ExpressionNode* Cedomp::Semantic::ComputeNot( ExpressionNode* val )
{

}

ExpressionNode* Cedomp::Semantic::ComputeLessEqual( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("<=");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
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
				throw BinaryOperationNotSupported(opName, left->getTypeCode(),
						right->getTypeCode());
			}
			//Coercion successful
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
}

ExpressionNode* Cedomp::Semantic::ComputeLess( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("<");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
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
				throw BinaryOperationNotSupported(opName, left->getTypeCode(),
						right->getTypeCode());
			}
			//Coercion successful
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
}

ExpressionNode* Cedomp::Semantic::ComputeEnclosed( ExpressionNode* val )
{
	return val;
}
