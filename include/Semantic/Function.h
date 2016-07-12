/*
 * Function.h
 *
 *  Created on: Jul 12, 2016
 *      Author: mitthy
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_
namespace Cedomp
{
	namespace Semantic
	{
		struct FunctionInfo {
			std::string name;
			std::vector<Cedomp::AST::VariableNode*>* args;
		};


		Cedomp::AST::FunctionNode* CreateFunction(FunctionInfo* functionInfo, Cedomp::AST::BlockNode* body);
	}
}

#endif /* FUNCTION_H_ */
