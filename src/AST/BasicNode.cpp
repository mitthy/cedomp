/*
 * BasicNode.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: mitthy
 */

#include "AST/BasicNode.h"
#include <iostream>
using namespace Cedomp::AST;

void BlockNode::addNode( AbstractNode* node )
{
	nodes.push_back(node);
}
void BlockNode::printNode() const
{
	for (auto node : nodes)
	{
		node->printNode();
		std::cout << std::endl;
	}
}
BlockNode::~BlockNode()
{
	for (AbstractNode* node : nodes)
	{
		delete node;
	}
}

void SemanticErrorNode::printNode() const
{
	std::cout << "semantic error ocurred in this branch";
}


void AbstractNode::searchReturnValue(std::vector<ExpressionNode*>& output) const
{
	//Default implementation
}

void BlockNode::searchReturnValue(std::vector<ExpressionNode*>& output) const
{
	for(auto& node : nodes)
	{
		node->searchReturnValue(output);
	}
}
