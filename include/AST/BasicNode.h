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
		class AbstractNode
		{
		public:
			virtual void printNode() const = 0;
			virtual ~AbstractNode() = default;
		};

		class BlockNode: public AbstractNode
		{
		public:
			void addNode( AbstractNode* node );
			virtual void printNode() const;
			virtual ~BlockNode();
		private:
			std::vector<AbstractNode*> nodes;
		};

	}
}

#endif /* BASICNODE_H_ */
