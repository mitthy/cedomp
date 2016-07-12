/*
 * Expression.h
 *
 *  Created on: Jul 7, 2016
 *      Author: mitthy
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_
#include <string>
#include "AST/AST.h"
namespace Cedomp
{
	namespace Semantic
	{

		AST::ExpressionNode* ComputeInteger(long * val);

		AST::ExpressionNode* ComputeFloat(double* val);

		AST::ExpressionNode* ComputeBool(bool * val);

		AST::ExpressionNode* ComputeID(char * val);

		AST::ExpressionNode* ComputeString(std::string * val);

		AST::ExpressionNode* ComputeMap(std::map<std::string, void*>* val);

		AST::ExpressionNode* ComputeList(std::vector<void*>* val);

		AST::ExpressionNode* ComputeIndex(char * id, AST::ExpressionNode* val);

		AST::ExpressionNode* ComputeMod(AST::ExpressionNode* left, AST::ExpressionNode* right);

		AST::ExpressionNode* ComputeAddition(AST::ExpressionNode* left, AST::ExpressionNode* right);

		AST::ExpressionNode* ComputeSubtraction(AST::ExpressionNode* left, AST::ExpressionNode* right);

		AST::ExpressionNode* ComputeMultiplication(AST::ExpressionNode* left, AST::ExpressionNode* right);

		AST::ExpressionNode* ComputeDivision(AST::ExpressionNode* left, AST::ExpressionNode* right);

		AST::ExpressionNode* ComputeUnaryMinus(AST::ExpressionNode* val);

		AST::ExpressionNode* ComputeGreaterThan(AST::ExpressionNode* left, AST::ExpressionNode* right);

		AST::ExpressionNode* ComputeEquals(AST::ExpressionNode* left, AST::ExpressionNode* right);

		AST::ExpressionNode* ComputeDifferent(AST::ExpressionNode* left, AST::ExpressionNode* right);

		AST::ExpressionNode* ComputeGreaterEquals(AST::ExpressionNode* left, AST::ExpressionNode* right);

		AST::ExpressionNode* ComputeAnd(AST::ExpressionNode* left, AST::ExpressionNode* right);

		AST::ExpressionNode* ComputeXor(AST::ExpressionNode* left, AST::ExpressionNode* right);

		AST::ExpressionNode* ComputeOr(AST::ExpressionNode* left, AST::ExpressionNode* right);

		AST::ExpressionNode* ComputeNot(AST::ExpressionNode* val);

		AST::ExpressionNode* ComputeLessEqual(AST::ExpressionNode* left, AST::ExpressionNode* right);

		AST::ExpressionNode* ComputeLess(AST::ExpressionNode* left, AST::ExpressionNode* right);

		AST::ExpressionNode* ComputeEnclosed(AST::ExpressionNode* val);

		AST::ExpressionNode* ComputeLenght(AST::ExpressionNode* val);

		//TODO: Function call

	}
}



#endif /* EXPRESSION_H_ */
