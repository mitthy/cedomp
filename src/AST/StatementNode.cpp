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
	if(!index)
	{
		std::cout << "assigning var " << id << " = ";
	}
	else
	{
		auto& scope = Cedomp::Scope::Scope::getScope();
		auto varSymbol = scope.searchScope(id);
		if(varSymbol)
		{
			auto typeName = Cedomp::Type::Type::getTypeName(varSymbol->type);
			std::cout << "assigning var {type:" << typeName << "} " << id << "[";
			index->printNode();
			std::cout << "] = ";
		}
		else
		{
			std::cerr << "Shouldn't get here" << std::endl;
		}
	}
	this->expr->printNode();
}

void AssignBlockNode::addNode( AbstractNode* node )
{
	nodes.push_back(node);
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

AssignBlockNode::~AssignBlockNode()
{
	for (auto node : nodes)
	{
		delete node;
	}
}
