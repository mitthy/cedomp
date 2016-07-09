/*
 * VarAssign.h
 *
 *  Created on: Jul 7, 2016
 *      Author: mitthy
 */

#ifndef VARASSIGN_H_
#define VARASSIGN_H_
#include <string>
#include <vector>
#include "AST/AST.h"
namespace Cedomp
{
	namespace Semantic
	{

		struct VarNameIndex
		{
			AST::ExpressionNode* index;
			std::string varName;
		};

		std::vector<VarNameIndex>* ParseVarNames(
				std::vector<VarNameIndex>* previous, std::string varName );

		std::vector<VarNameIndex>* ParseVarNames(
						std::vector<VarNameIndex>* previous, std::string varName, AST::ExpressionNode* index );

		std::vector<AST::ExpressionNode*>* ParseAssignExpressions(
				std::vector<AST::ExpressionNode*>*, AST::ExpressionNode* );

		std::vector<AST::AssignVariableNode*>* AssignVariable(
				std::vector<VarNameIndex>* ids,
				std::vector<AST::ExpressionNode*>* values );

	}
}

#endif /* VARASSIGN_H_ */
