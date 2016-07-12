/*
 * Statement.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: mitthy
 */
#include "AST/AST.h"
#include "Semantic/Statement.h"
#include <vector>
#include <memory>
#include "Exceptions/TypeExceptions.h"
#include <iostream>
using namespace Cedomp::AST;

AbstractNode * Cedomp::Semantic::AssignVariableStatement(
		std::vector<AssignVariableNode*>* nodes )
{
	std::unique_ptr<AST::AssignBlockNode> retRAII(new AssignBlockNode());
	for (auto node : (*nodes))
	{
		retRAII->addNode(node);
	}
	AssignBlockNode* ret = retRAII.release();
	delete nodes;
	return ret;
}

BlockNode* Cedomp::Semantic::AddStatement( BlockNode* block,
		AbstractNode* statement )
{
	std::unique_ptr<AST::BlockNode> blockRAII(block);
	BlockNode* ret = block;
	if (!ret)
	{
		ret = new BlockNode();
	}
	if (statement)
	{
		ret->addNode(statement);
	}
	else
	{
		ret->addNode(new SemanticErrorNode());
	}
	blockRAII.release();
	return ret;
}

AbstractNode* Cedomp::Semantic::ExpressionStatement( ExpressionNode* expr )
{
	return expr;
}

AbstractNode* Cedomp::Semantic::IfStatement( ExpressionNode* condition,
		BlockNode* body )
{
	if (!Cedomp::Type::Type::isCompatible(Cedomp::Type::BaseType::TYPEBOOL,
			condition->getTypeCode()))
	{
		throw Cedomp::Exceptions::IncompatibleTypeException(
				condition->getTypeCode(), Cedomp::Type::BaseType::TYPEBOOL);
	}
	if (condition->getTypeCode() != Cedomp::Type::TYPEBOOL)
	{
		condition->setCoercion(Cedomp::Type::TYPEBOOL, Cedomp::Type::TYPEGENERIC);
	}
	if (body == nullptr)
	{
		return new Cedomp::AST::IfNode(condition);
	}
	else
	{
		return new Cedomp::AST::IfNode(condition, body);
	}
}

AbstractNode* Cedomp::Semantic::IfStatement( ExpressionNode* condition,
		BlockNode* body, BlockNode* elseBody )
{

	if (!Cedomp::Type::Type::isCompatible(Cedomp::Type::BaseType::TYPEBOOL,
			condition->getTypeCode()))
	{
		throw Cedomp::Exceptions::IncompatibleTypeException(
				condition->getTypeCode(), Cedomp::Type::BaseType::TYPEBOOL);
	}
	if (condition->getTypeCode() != Cedomp::Type::TYPEBOOL)
	{
		condition->setCoercion(Cedomp::Type::TYPEBOOL, Cedomp::Type::TYPEGENERIC);
	}
	if (body == nullptr)
	{
		body = new BlockNode();
	}
	if (elseBody == nullptr)
	{
		elseBody = new BlockNode();
	}
	return new Cedomp::AST::IfNode(condition, body, elseBody);

}

AbstractNode* Cedomp::Semantic::ParseFor( ExpressionNode* condition,
		BlockNode* body )
{
	if (!Cedomp::Type::Type::isCompatible(Cedomp::Type::BaseType::TYPEBOOL,
			condition->getTypeCode()))
	{
		throw Cedomp::Exceptions::IncompatibleTypeException(
				condition->getTypeCode(), Cedomp::Type::BaseType::TYPEBOOL);
	}
	if (condition->getTypeCode() != Cedomp::Type::TYPEBOOL)
	{
		condition->setCoercion(Cedomp::Type::TYPEBOOL, Cedomp::Type::TYPEGENERIC);
	}
	return new Cedomp::AST::WhileNode(condition, body);
}
