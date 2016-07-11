/*
 * ExpressionNode.h
 *
 *  Created on: Jul 10, 2016
 *      Author: mitthy
 */

#ifndef EXPRESSIONNODE_H_
#define EXPRESSIONNODE_H_

#include "Type/Types.h"
#include "BasicNode.h"
#include <string>
#include <memory>
#include <map>
namespace Cedomp
{
	namespace AST
	{

		class ExpressionNode: public AbstractNode
		{
		public:
			ExpressionNode( Type::TypeCode type );
			virtual ~ExpressionNode() = default;
			Type::TypeCode getTypeCode();
			virtual void printNode() const;
		protected:
			Type::TypeCode type;
			virtual void printExpressionValue() const = 0;
		};

		class VariableNode: public ExpressionNode
		{
		public:
			VariableNode( std::string name, Type::TypeCode type );
		protected:
			virtual void printExpressionValue() const;
		private:
			std::string varName;
		};

		class IntegerNode: public ExpressionNode
		{
		public:
			IntegerNode( long* val );
		protected:
			virtual void printExpressionValue() const;
		private:
			std::shared_ptr<long> value;
		};

		class FloatNode: public ExpressionNode
		{
		public:
			FloatNode( double* val );
		protected:
			virtual void printExpressionValue() const;
		private:
			std::shared_ptr<double> value;
		};

		class BoolNode: public ExpressionNode
		{
		public:
			BoolNode( bool* val );
		protected:
			virtual void printExpressionValue() const;
		private:
			std::shared_ptr<bool> value;
		};

		class StringNode: public ExpressionNode
		{
		public:
			StringNode( std::string * val );
		protected:
			virtual void printExpressionValue() const;
		private:
			std::shared_ptr<std::string> value;
		};

		class MapNode : public ExpressionNode
		{
		public:
			MapNode(std::map<std::string, void*>* val);
			virtual void printExpressionValue() const;
		private:
			std::shared_ptr<std::map<std::string, void*>> value;
		};

	}
}
#endif /* EXPRESSIONNODE_H_ */
