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
	std::cout << "{ " << typeName << ": ";
	printExpressionValue();
	std::cout << "}";
}

ExpressionNode::ExpressionNode( Type::TypeCode type ) :
		type(type)
{
}

Cedomp::Type::TypeCode ExpressionNode::getTypeCode()
{
	return this->type;
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

