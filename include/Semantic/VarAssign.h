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

		std::vector<std::string>* ParseVarNames(
				std::vector<std::string>* previous, std::string varName );

		std::vector<AST::ExpressionNode*>* ParseAssignExpressions(
				std::vector<AST::ExpressionNode*>*, AST::ExpressionNode* );

		std::vector<AST::AssignVariableNode*>* AssignVariable(
				const std::vector<std::string>* const ids,
				const std::vector<AST::ExpressionNode*>* const values );

	}
}

#endif /* VARASSIGN_H_ */
