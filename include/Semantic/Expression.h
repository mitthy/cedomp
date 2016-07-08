/*
 * Expression.h
 *
 *  Created on: Jul 7, 2016
 *      Author: mitthy
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

namespace Cedomp
{
	namespace Semantic
	{

		AST::ExpressionNode* ComputeInteger();

		AST::ExpressionNode* ComputeFloat();

		AST::ExpressionNode* ComputeBool();

		AST::ExpressionNode* ComputeID();

		AST::ExpressionNode* ComputeString();

		AST::ExpressionNode* ComputeMap();

		AST::ExpressionNode* ComputeList();

		AST::ExpressionNode* ComputeIndex();

		AST::ExpressionNode* ComputeMod();

		AST::ExpressionNode* ComputeAddition();

		AST::ExpressionNode* ComputeSubtraction();

		AST::ExpressionNode* ComputeMultiplication();

		AST::ExpressionNode* ComputeDivision();

		AST::ExpressionNode* ComputeUnaryMinus();

		AST::ExpressionNode* ComputeGreaterThan();

		AST::ExpressionNode* ComputeEquals();

		AST::ExpressionNode* ComputeDifferent();

		AST::ExpressionNode* ComputeGreaterEquals();

		AST::ExpressionNode* ComputeAnd();

		AST::ExpressionNode* ComputeXor();

		AST::ExpressionNode* ComputeOr();

		AST::ExpressionNode* ComputeNot();

		AST::ExpressionNode* ComputeLessEqual();

		AST::ExpressionNode* ComputeLess();

		AST::ExpressionNode* ComputeEnclosed();

		AST::ExpressionNode* ComputeFunctionCall();

	}
}



#endif /* EXPRESSION_H_ */
