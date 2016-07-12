/*
 * ExpressionNode.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: mitthy
 */

#include "AST/ExpressionNode.h"
#include <iostream>
#include "Type/Types.h"
using namespace Cedomp::AST;

void ExpressionNode::printNode() const
{
	auto typeName = Cedomp::Type::Type::getTypeName(type);
	std::cout << "{" << typeName << ": ";
	printExpressionValue();
	std::cout << "}";
}

ExpressionNode::ExpressionNode( Type::TypeCode type ) :
		type(type), genericTypeCode(Cedomp::Type::BaseType::TYPEGENERIC)
{
}

Cedomp::Type::TypeCode ExpressionNode::getTypeCode() const
{
	return this->type;
}

Cedomp::Type::TypeCode ExpressionNode::getGenericTypeCode() const
{
	return genericTypeCode;
}

void ExpressionNode::setGenericTypeCode( Cedomp::Type::TypeCode generic )
{
	genericTypeCode = generic;
}

VariableNode::VariableNode( std::string name, Type::TypeCode type ) :
		ExpressionNode(type), varName(name)
{

}

void VariableNode::printExpressionValue() const
{
	std::cout << "Var: " << varName;
}

IntegerNode::IntegerNode( long* val ) :
		ExpressionNode(Type::BaseType::TYPEINT), value(val)
{

}

void IntegerNode::printExpressionValue() const
{
	std::cout << *value;
}

FloatNode::FloatNode( double* val ) :
		ExpressionNode(Type::BaseType::TYPEFLOAT), value(val)
{
}

void FloatNode::printExpressionValue() const
{
	std::cout << *value;
}

BoolNode::BoolNode( bool* val ) :
		ExpressionNode(Type::BaseType::TYPEBOOL), value(val)
{
}

void BoolNode::printExpressionValue() const
{
	bool booleanValue = *value;
	if (booleanValue)
	{
		std::cout << "true";
	}
	else
	{
		std::cout << "false";
	}
}

StringNode::StringNode( std::string * val ) :
		ExpressionNode(Cedomp::Type::BaseType::TYPESTRING), value(val)
{

}

void StringNode::printExpressionValue() const
{
	std::cout << *value;
}

MapNode::MapNode( std::map<std::string, void*>* val ) :
		ExpressionNode(Cedomp::Type::BaseType::TYPEMAP), value(val)
{
}

void MapNode::printExpressionValue() const
{
	std::cout << "new map";
}

ListNode::ListNode( std::vector<void*>* val ) :
		ExpressionNode(Cedomp::Type::BaseType::TYPELIST), value(val)
{

}

void ListNode::printExpressionValue() const
{
	std::cout << "new list";
}

IndexNode::IndexNode( Cedomp::Type::TypeCode type, std::string varName,
		ExpressionNode* index ) :
		ExpressionNode(type), varName(varName), index(index)
{

}
void IndexNode::printExpressionValue() const
{
	std::cout << "{" << varName << "[";
	index->printNode();
	std::cout << "]" << "}";
}

BinaryOperationNode::BinaryOperationNode( Cedomp::Type::TypeCode type,
		ExpressionNode* lhs, ExpressionNode* rhs, bool coercion ) :
		ExpressionNode(type), lhs(lhs), rhs(rhs), coercion(coercion)
{

}

void BinaryOperationNode::printExpressionValue() const
{
	lhs->printNode();
	std::cout << " ";
	printOpName();
	std::cout << " ";
	if (coercion)
	{
		auto typeName = Cedomp::Type::Type::getTypeName(lhs->getTypeCode());
		std::cout << "(" << typeName << ") ";
	}
	rhs->printNode();
}

ModNode::ModNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
		ExpressionNode* rhs, bool coercion ) :
		BinaryOperationNode(type, lhs, rhs, coercion)
{

}

void ModNode::printOpName() const
{
	std::cout << "mod";
}

AdditionNode::AdditionNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
		ExpressionNode* rhs, bool coercion ) :
		BinaryOperationNode(type, lhs, rhs, coercion)
{

}

void AdditionNode::printOpName() const
{
	std::cout << "+";
}

SubtractionNode::SubtractionNode( Cedomp::Type::TypeCode type,
		ExpressionNode* lhs, ExpressionNode* rhs, bool coercion ) :
		BinaryOperationNode(type, lhs, rhs, coercion)
{

}
void SubtractionNode::printOpName() const
{
	std::cout << "-";
}

MultiplicationNode::MultiplicationNode( Cedomp::Type::TypeCode type,
		ExpressionNode* lhs, ExpressionNode* rhs, bool coercion ) :
		BinaryOperationNode(type, lhs, rhs, coercion)
{

}
void MultiplicationNode::printOpName() const
{
	std::cout << "*";
}

DivisionNode::DivisionNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
		ExpressionNode* rhs, bool coercion ) :
		BinaryOperationNode(type, lhs, rhs, coercion)
{
}
void DivisionNode::printOpName() const
{
	std::cout << "/";
}

EqualsNode::EqualsNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
		ExpressionNode* rhs, bool coercion ) :
		BinaryOperationNode(type, lhs, rhs, coercion)
{

}
void EqualsNode::printOpName() const
{
	std::cout << "==";
}

DifferentNode::DifferentNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
		ExpressionNode* rhs, bool coercion ) :
		BinaryOperationNode(type, lhs, rhs, coercion)
{

}
void DifferentNode::printOpName() const
{
	std::cout << "!=";
}

GreaterNode::GreaterNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
		ExpressionNode* rhs, bool coercion ) :
		BinaryOperationNode(type, lhs, rhs, coercion)
{

}
void GreaterNode::printOpName() const
{
	std::cout << ">";
}

LessNode::LessNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
		ExpressionNode* rhs, bool coercion ) :
		BinaryOperationNode(type, lhs, rhs, coercion)
{

}
void LessNode::printOpName() const
{
	std::cout << "<";
}

GreaterEqualNode::GreaterEqualNode( Cedomp::Type::TypeCode type,
		ExpressionNode* lhs, ExpressionNode* rhs, bool coercion ) :
		BinaryOperationNode(type, lhs, rhs, coercion)
{

}
void GreaterEqualNode::printOpName() const
{
	std::cout << ">=";
}

LessEqualNode::LessEqualNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
		ExpressionNode* rhs, bool coercion ) :
		BinaryOperationNode(type, lhs, rhs, coercion)
{

}
void LessEqualNode::printOpName() const
{
	std::cout << "<=";
}

AndNode::AndNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
		ExpressionNode* rhs, bool coercion ) :
		BinaryOperationNode(type, lhs, rhs, coercion)
{

}
void AndNode::printOpName() const
{
	std::cout << "and";
}

OrNode::OrNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
		ExpressionNode* rhs, bool coercion ) :
		BinaryOperationNode(type, lhs, rhs, coercion)
{

}
void OrNode::printOpName() const
{
	std::cout << "or";
}

XorNode::XorNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
		ExpressionNode* rhs, bool coercion ) :
		BinaryOperationNode(type, lhs, rhs, coercion)
{

}
void XorNode::printOpName() const
{
	std::cout << "xor";
}

UnaryOperationNode::UnaryOperationNode( Cedomp::Type::TypeCode type,
		ExpressionNode* expr ) :
		ExpressionNode(type), expr(expr)
{

}

void UnaryOperationNode::printExpressionValue() const
{
	printOpName();
	std::cout << " ";
	expr->printNode();
}

UnaryMinusNode::UnaryMinusNode( Cedomp::Type::TypeCode type,
		ExpressionNode* expr ) :
		UnaryOperationNode(type, expr)
{
}

void UnaryMinusNode::printOpName() const
{
	std::cout << "-";
}

NotNode::NotNode( Cedomp::Type::TypeCode type, ExpressionNode* expr ) :
		UnaryOperationNode(type, expr)
{
}

void NotNode::printOpName() const
{
	"not";
}

