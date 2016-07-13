/*
 * BasicNode.h
 *
 *  Created on: Jul 10, 2016
 *      Author: mitthy
 */

#ifndef BASICNODE_H_
#define BASICNODE_H_
#include <vector>
namespace Cedomp
{
	namespace AST
	{
		class ExpressionNode;

		class AbstractNode
		{
		public:
			virtual void printNode() const = 0;
			virtual ~AbstractNode() = default;
			virtual void searchReturnValue(std::vector<ExpressionNode*>& output) const;
		};

		class BlockNode: public AbstractNode
		{
		public:
			void addNode( AbstractNode* node );
			virtual void printNode() const;
			virtual ~BlockNode();
			virtual void searchReturnValue(std::vector<ExpressionNode*>& output) const;
		private:
			std::vector<AbstractNode*> nodes;
		};

		class SemanticErrorNode: public AbstractNode
		{
		public:
			virtual void printNode() const;
		};

	}
}

#endif /* BASICNODE_H_ */
