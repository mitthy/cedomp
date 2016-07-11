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
#include <memory>
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
			std::unique_ptr<ExpressionNode> expr;
			std::unique_ptr<ExpressionNode> index;
		};

		class AssignBlockNode: public AbstractNode
		{
		public:
			void addNode( AssignVariableNode* node );
			virtual void printNode() const;
		private:
			std::vector<std::unique_ptr<AssignVariableNode>> nodes;
		};

	}
}

#endif /* STATEMENTNODE_H_ */
