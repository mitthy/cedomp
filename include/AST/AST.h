/*
 * AST.h
 *
 *  Created on: Jul 7, 2016
 *      Author: mitthy
 */

#ifndef AST_H_
#define AST_H_
#include "Type/Types.h"
namespace Cedomp
{
	namespace AST
	{
		class AbstractNode
		{

		};

		class ExpressionNode
		{
		public:
			Type::TypeCode getTypeCode();
		private:
			Type::TypeCode type;
		};

		class VariableNode
		{

		};

		class AssignVariableNode
		{
		public:
			AssignVariableNode(std::string string, ExpressionNode* expr);
		};

	}
}

#endif /* AST_H_ */
