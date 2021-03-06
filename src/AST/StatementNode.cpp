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
#include <cstdlib>
using namespace Cedomp::AST;

AssignVariableNode::AssignVariableNode( std::string string,
		ExpressionNode* expr ) :
		id(string), expr(expr), index(nullptr), scope(
				Cedomp::Scope::Scope::getScope().getCurrentScope())

{

}

AssignVariableNode::AssignVariableNode( std::string string,
		ExpressionNode* index, ExpressionNode* expr ) :
		id(string), expr(expr), index(index), scope(
				Cedomp::Scope::Scope::getScope().getCurrentScope())
{

}

void AssignVariableNode::printNode() const
{
	if (!index)
	{
		auto varSymbol = scope->searchScope(id);
		if (varSymbol)
		{
			//Check for coercion
			auto type = varSymbol->type;
			auto varTypeGeneric = varSymbol->genericType;
			std::cout << "assigning var " << "{type:"
					<< Cedomp::Type::Type::getTypeName(type);
			if (varTypeGeneric != Cedomp::Type::TYPEGENERIC
					&& varTypeGeneric != Cedomp::Type::TYPEERROR)
			{
				std::cout << ":"
						<< Cedomp::Type::Type::getTypeName(varTypeGeneric);
			}
			std::cout << "} " << id << " = ";
		}
		else
		{
			std::cerr << "BUG" << std::endl;
			std::exit(-1);
		}
	}
	else
	{
		auto varSymbol = scope->searchScope(id);
		if (varSymbol)
		{
			auto typeName = Cedomp::Type::Type::getTypeName(varSymbol->type);
			std::cout << "assigning var {type:" << typeName;
			auto varTypeGeneric = varSymbol->genericType;
			if (varTypeGeneric != Cedomp::Type::TYPEGENERIC
					&& varTypeGeneric != Cedomp::Type::TYPEERROR)
			{
				std::cout << ":"
						<< Cedomp::Type::Type::getTypeName(varTypeGeneric);
			}
			std::cout << "} " << id << "[";
			index->printNode();
			std::cout << "] = ";
		}
		else
		{
			std::cerr << "BUG" << std::endl;
			std::exit(-1);
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

IfNode::IfNode( ExpressionNode* condition ) :
		condition(condition), thenBody(nullptr), elseBody(nullptr)
{

}
IfNode::IfNode( ExpressionNode* condition, BlockNode* thenBody ) :
		condition(condition), thenBody(thenBody), elseBody(nullptr)
{

}
IfNode::IfNode( ExpressionNode* condition, BlockNode* thenBody,
		BlockNode* elseBody ) :
		condition(condition), thenBody(thenBody), elseBody(elseBody)
{

}

void IfNode::searchReturnValue( std::vector<ExpressionNode*>& output ) const
{
	if (thenBody)
	{
		thenBody->searchReturnValue(output);
	}
	if (elseBody)
	{
		elseBody->searchReturnValue(output);
	}
}

void IfNode::printNode() const
{
	std::cout << "if ";
	condition->printNode();
	if (thenBody)
	{
		std::cout << std::endl << "then" << std::endl;
		thenBody->printNode();
		if (elseBody)
		{
			std::cout << "else" << std::endl;
			elseBody->printNode();
		}
	}
	std::cout << "end";

}

WhileNode::WhileNode( ExpressionNode* condition, BlockNode* body ) :
		condition(condition), body(body)
{

}

void WhileNode::searchReturnValue( std::vector<ExpressionNode*>& output ) const
{
	if (body)
	{
		body->searchReturnValue(output);
	}
}

void WhileNode::printNode() const
{
	std::cout << "while ";
	condition->printNode();
	std::cout << std::endl;
	body->printNode();
	std::cout << "end";
}

ReturnNode::ReturnNode( ExpressionNode* expr ) :
		retValue(expr)
{

}

void ReturnNode::searchReturnValue( std::vector<ExpressionNode*>& output ) const
{
	output.push_back(this->retValue.get());
}

void ReturnNode::printNode() const
{
	std::cout << "return ";
	retValue->printNode();
}

FunctionNode::FunctionNode( std::string id,
		std::vector<Cedomp::AST::ExpressionNode*>*args,
		Cedomp::Type::TypeCode returnType, Cedomp::Type::TypeCode genericType,
		BlockNode* body ) :
		id(id), returnType(returnType), genericType(genericType), body(body)
{
	if (args)
	{
		for (auto& el : (*args))
		{
			std::shared_ptr<ExpressionNode> toAdd(el);
			this->args.push_back(toAdd);
		}
		delete args;
	}

}

void FunctionNode::printNode() const
{
	std::cout << "function " << id << ": {type:"
			<< Cedomp::Type::Type::getTypeName(returnType);
	if (genericType != Cedomp::Type::TYPEGENERIC
			&& genericType != Cedomp::Type::TYPEDYNAMIC)
	{
		std::cout << ":" << Cedomp::Type::Type::getTypeName(genericType);
	}
	std::cout << "}" << std::endl;
	std::cout << "args beg" << std::endl;
	for (auto& arg : args)
	{
		arg->printNode();
		std::cout << std::endl;
	}
	std::cout << "args end" << std::endl;
	body->printNode();
	std::cout << "end";
}

