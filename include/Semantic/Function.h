/*
 * Function.h
 *
 *  Created on: Jul 12, 2016
 *      Author: mitthy
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_
#include "AST/AST.h"
#include <vector>

namespace Cedomp
{
	namespace Semantic
	{
		struct FunctionInfo
		{
			std::string name;
			std::vector<Cedomp::AST::VariableNode*>* args;
		};

		AST::FunctionNode* CreateFunction( FunctionInfo* functionInfo,
				AST::BlockNode* body );

		std::vector<std::string>* ParseArgList(
				std::vector<std::string>*, char* id );

		FunctionInfo* AddFunctionToScope(char* name, std::vector<std::string>* args);

	}
}

#endif /* FUNCTION_H_ */
