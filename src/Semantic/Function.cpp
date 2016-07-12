/*
 * Function.cpp
 *
 *  Created on: Jul 12, 2016
 *      Author: mitthy
 */
#include "AST/AST.h"
#include "Semantic/Function.h"
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace Cedomp::AST;
using Cedomp::Semantic::FunctionInfo;

FunctionNode* Cedomp::Semantic::CreateFunction( FunctionInfo* functionInfo,
		BlockNode* body )
{
	return nullptr;
}

std::vector<std::string>* Cedomp::Semantic::ParseArgList(
		std::vector<std::string>* previous, char* id )
{
	std::string expr(id);
	std::vector<std::string>* result = previous;
	if(!result)
	{
		result = new std::vector<std::string>();
	}
	//Add id to scope
	Cedomp::Scope::Scope::getScope().addToScope(expr, Cedomp::Type::TYPEGENERIC);
	result->push_back(expr);
	return result;
}

FunctionInfo* Cedomp::Semantic::AddFunctionToScope(char* name, std::vector<std::string>* args)
{

}
