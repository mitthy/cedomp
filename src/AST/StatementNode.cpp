/*
 * StatementNode.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: mitthy
 */

#include "AST/StatementNode.h"
#include "Scope/Scope.h"
#include "Type/Types.h"
#include <iostream>
#include <memory>
using namespace Cedomp::AST;

AssignVariableNode::AssignVariableNode( std::string string,
		ExpressionNode* expr ) :
		id(string), expr(expr), index(nullptr)
{

}

AssignVariableNode::AssignVariableNode( std::string string,
		ExpressionNode* index, ExpressionNode* expr ) :
		id(string), expr(expr), index(index)
{

}

void AssignVariableNode::printNode() const
{
	if (!index)
	{
		auto& scope = Cedomp::Scope::Scope::getScope();
		auto varSymbol = scope.searchScope(id);
		if (varSymbol)
		{
			//Check for coercion
			auto type = varSymbol->type;
			auto typeExpr = expr->getTypeCode();
			std::cout << "assigning var " << id << " = ";
			if (type != typeExpr)
			{
				std::cout << "(" << Cedomp::Type::Type::getTypeName(type)
						<< ") ";
			}
		}
		else
		{
			std::cerr << "Shouldn't get here" << std::endl;
		}
	}
	else
	{
		auto& scope = Cedomp::Scope::Scope::getScope();
		auto varSymbol = scope.searchScope(id);
		if (varSymbol)
		{
			auto typeExpr = expr->getTypeCode();
			auto typeName = Cedomp::Type::Type::getTypeName(varSymbol->type);
			std::cout << "assigning var {type:" << typeName << "} " << id
					<< "[";
			index->printNode();
			std::cout << "] = ";
			auto type = varSymbol->genericType;
			if (type != typeExpr)
			{
				std::cout << "(" << Cedomp::Type::Type::getTypeName(type)
						<< ") ";
			}
		}
		else
		{
			std::cerr << "Shouldn't get here" << std::endl;
		}
	}
	this->expr->printNode();
}

void AssignBlockNode::addNode( AssignVariableNode* node )
{
	nodes.push_back(std::unique_ptr<AssignVariableNode>(node));
}

void AssignBlockNode::printNode() const
{
	if (!nodes.empty())
	{
		auto end = nodes.end();
		auto it = nodes.begin();
		for (; it != end - 1; ++it)
		{
			(*it)->printNode();
			std::cout << std::endl;
		}
		(*it)->printNode();
	}
}

