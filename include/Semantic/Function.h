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
#include "Type/Types.h"
#include <algorithm>
namespace Cedomp
{
	namespace Semantic
	{
		struct FunctionInfo
		{
			std::string name;
			std::vector<Cedomp::AST::ExpressionNode*>* args;
		};

		AST::FunctionNode* CreateFunction( FunctionInfo* functionInfo,
				AST::BlockNode* bodyInfo );

		std::vector<AST::ExpressionNode*>* ParseArgList(
				std::vector<AST::ExpressionNode*>*, AST::ExpressionNode* id );

		FunctionInfo* AddFunctionToScope( char* name,
				std::vector<AST::ExpressionNode*>* args );

		FunctionInfo* AddFunctionToScope( char* name );

		AST::BlockNode* ParseFunctionBody( AST::BlockNode* body );

		AST::ReturnNode* CheckReturnStatement( AST::ExpressionNode* expr );

		std::vector<AST::ExpressionNode*>* PassParameters(
				std::vector<AST::ExpressionNode*>* list,
				AST::ExpressionNode* next );

		AST::ExpressionNode* CheckParameters( char* id );

		AST::ExpressionNode* CheckParameters( char* id, std::vector<AST::ExpressionNode*>* params );
	}
}

#endif /* FUNCTION_H_ */
