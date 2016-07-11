/*
 * StatementNode.h
 *
 *  Created on: Jul 10, 2016
 *      Author: mitthy
 */

#ifndef STATEMENTNODE_H_
#define STATEMENTNODE_H_
#include <string>
#include "BasicNode.h"
#include "ExpressionNode.h"
#include <vector>

namespace Cedomp
{
	namespace AST
	{

		class StatementNode: public AbstractNode
		{
		public:
			virtual ~StatementNode() = default;
		};

		class AssignVariableNode: public StatementNode
		{
		public:
			AssignVariableNode( std::string string, ExpressionNode* expr );
			AssignVariableNode( std::string string, ExpressionNode* index,
					ExpressionNode* expr );
			virtual void printNode() const;
		private:
			std::string id;
			ExpressionNode* expr;
			ExpressionNode* index;
		};

		class AssignBlockNode: public AbstractNode
		{
		public:
			void addNode( AbstractNode* node );
			virtual void printNode() const;
			virtual ~AssignBlockNode();
		private:
			std::vector<AbstractNode*> nodes;
		};

	}
}

#endif /* STATEMENTNODE_H_ */
