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
			if(checker != Cedomp::Type::BaseType::TYPEGENERIC)
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

ExpressionNode* Cedomp::Semantic::ComputeMod( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("mod");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
	bool coercion = false;
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
			coercion = true;
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
	return new ModNode(checker, left, right, coercion);
}

ExpressionNode* Cedomp::Semantic::ComputeAddition( ExpressionNode* left,
		ExpressionNode* right )
{
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), "+",
			right->getTypeCode(), checker);
	bool coercion = false;
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
			coercion = true;
		}
		else
		{
			throw BinaryOperationNotSupported("+", left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
	return new AdditionNode(checker, left, right, coercion);

}

ExpressionNode* Cedomp::Semantic::ComputeSubtraction( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("-");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
	bool coercion = false;
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
			coercion = true;
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
	return new SubtractionNode(checker, left, right, coercion);
}

ExpressionNode* Cedomp::Semantic::ComputeMultiplication( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("*");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
	bool coercion = false;
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
			coercion = true;
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
	return new MultiplicationNode(checker, left, right, coercion);
}

ExpressionNode* Cedomp::Semantic::ComputeDivision( ExpressionNode* left,
		ExpressionNode* right )
{
	std::string opName("/");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
	bool coercion = false;
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
			coercion = true;
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
	return new DivisionNode(checker, left, right, coercion);
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
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
	bool coercion = false;
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
			coercion = true;
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
	return new GreaterNode(checker, left, right, coercion);
}

ExpressionNode * Cedomp::Semantic::ComputeEquals( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName("==");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
	bool coercion = false;
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
			coercion = true;
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
	return new EqualsNode(checker, left, right, coercion);
}

ExpressionNode * Cedomp::Semantic::ComputeDifferent( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName("!=");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
	bool coercion = false;
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
			coercion = true;
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
	return new DifferentNode(checker, left, right, coercion);
}

ExpressionNode * Cedomp::Semantic::ComputeGreaterEquals( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName(">=");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
	bool coercion = false;
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
			coercion = true;
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
	return new GreaterEqualNode(checker, left, right, coercion);
}

ExpressionNode * Cedomp::Semantic::ComputeAnd( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName("and");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
	bool coercion = false;
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
			coercion = true;
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
	return new AndNode(checker, left, right, coercion);
}

ExpressionNode * Cedomp::Semantic::ComputeXor( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName("xor");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
	bool coercion = false;
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
			coercion = true;
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	return new XorNode(checker, left, right, coercion);
	//Return new node here.
}

ExpressionNode * Cedomp::Semantic::ComputeOr( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName("or");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
	bool coercion = false;
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
			coercion = true;
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
	return new OrNode(checker, left, right, coercion);
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
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
	bool coercion = false;
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
			coercion = true;
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
	return new LessEqualNode(checker, left, right, coercion);
}

ExpressionNode * Cedomp::Semantic::ComputeLess( ExpressionNode * left,
		ExpressionNode * right )
{
	std::string opName("<");
	auto& operation = Cedomp::Type::Operation::getInstance();
	Cedomp::Type::TypeCode checker;
	operation.getReturnBinaryType(left->getTypeCode(), opName,
			right->getTypeCode(), checker);
	bool coercion = false;
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
			coercion = true;
		}
		else
		{
			throw BinaryOperationNotSupported(opName, left->getTypeCode(),
					right->getTypeCode());
		}
	}
	//Return new node here.
	return new LessNode(checker, left, right, coercion);
}

ExpressionNode * Cedomp::Semantic::ComputeEnclosed( ExpressionNode * val )
{
	return val;
}
