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
using namespace Cedomp::AST;

AbstractNode * Cedomp::Semantic::AssignVariableStatement(std::vector<AssignVariableNode*>*  nodes)
{
	std::unique_ptr<AST::AssignBlockNode> retRAII(new AssignBlockNode());
	for(auto node : (*nodes))
	{
		retRAII->addNode(node);
	}
	AssignBlockNode* ret = retRAII.release();
	delete nodes;
	return ret;
}


BlockNode* Cedomp::Semantic::AddStatement(BlockNode* block, AbstractNode* statement)
{
	std::unique_ptr<AST::BlockNode> blockRAII(block);
	BlockNode* ret = block;
	if(!ret)
	{
		ret = new BlockNode();
	}
	if(statement)
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
