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
			Type::TypeCode getTypeCode() const;
			Type::TypeCode getGenericTypeCode() const;
			void setGenericTypeCode( Type::TypeCode generic );
			void setCoercion( Type::TypeCode type, Type::TypeCode genericType );
			virtual void printNode() const;
		protected:
			Type::TypeCode type;
			Type::TypeCode genericTypeCode;
			Type::TypeCode coercionType;
			Type::TypeCode coercionGenericType;
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

		class MapNode: public ExpressionNode
		{
		public:
			MapNode( std::map<std::string, void*>* val );
		protected:
			virtual void printExpressionValue() const;
		private:
			std::shared_ptr<std::map<std::string, void*>> value;
		};

		class ListNode: public ExpressionNode
		{
		public:
			ListNode( std::vector<void*>* val );
		protected:
			virtual void printExpressionValue() const;
		private:
			std::shared_ptr<std::vector<void*>> value;
		};

		class IndexNode: public ExpressionNode
		{
		public:
			IndexNode( Cedomp::Type::TypeCode type, std::string varName,
					ExpressionNode* index );
		protected:
			virtual void printExpressionValue() const;
		private:
			std::unique_ptr<ExpressionNode> index;
			std::string varName;
		};

		class BinaryOperationNode: public ExpressionNode
		{
		public:
			BinaryOperationNode( Cedomp::Type::TypeCode type,
					ExpressionNode* lhs, ExpressionNode* rhs );
		protected:
			virtual void printExpressionValue() const;
			virtual void printOpName() const = 0;
			std::unique_ptr<ExpressionNode> lhs;
			std::unique_ptr<ExpressionNode> rhs;
		};

		class ModNode: public BinaryOperationNode
		{
		public:
			ModNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
					ExpressionNode* rhs );
		protected:
			virtual void printOpName() const;
		};

		class AdditionNode: public BinaryOperationNode
		{
		public:
			AdditionNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
					ExpressionNode* rhs );
		protected:
			virtual void printOpName() const;
		};

		class SubtractionNode: public BinaryOperationNode
		{
		public:
			SubtractionNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
					ExpressionNode* rhs );
		protected:
			virtual void printOpName() const;
		};

		class MultiplicationNode: public BinaryOperationNode
		{
		public:
			MultiplicationNode( Cedomp::Type::TypeCode type,
					ExpressionNode* lhs, ExpressionNode* rhs );
		protected:
			virtual void printOpName() const;
		};

		class DivisionNode: public BinaryOperationNode
		{
		public:
			DivisionNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
					ExpressionNode* rhs );
		protected:
			virtual void printOpName() const;
		};

		class EqualsNode: public BinaryOperationNode
		{
		public:
			EqualsNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
					ExpressionNode* rhs );
		protected:
			virtual void printOpName() const;
		};

		class DifferentNode: public BinaryOperationNode
		{
		public:
			DifferentNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
					ExpressionNode* rhs );
		protected:
			virtual void printOpName() const;
		};

		class GreaterNode: public BinaryOperationNode
		{
		public:
			GreaterNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
					ExpressionNode* rhs );
		protected:
			virtual void printOpName() const;
		};

		class LessNode: public BinaryOperationNode
		{
		public:
			LessNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
					ExpressionNode* rhs );
		protected:
			virtual void printOpName() const;
		};

		class GreaterEqualNode: public BinaryOperationNode
		{
		public:
			GreaterEqualNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
					ExpressionNode* rhs );
		protected:
			virtual void printOpName() const;
		};

		class LessEqualNode: public BinaryOperationNode
		{
		public:
			LessEqualNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
					ExpressionNode* rhs );
		protected:
			virtual void printOpName() const;
		};

		class AndNode: public BinaryOperationNode
		{
		public:
			AndNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
					ExpressionNode* rhs );
		protected:
			virtual void printOpName() const;
		};

		class OrNode: public BinaryOperationNode
		{
		public:
			OrNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
					ExpressionNode* rhs );
		protected:
			virtual void printOpName() const;
		};

		class XorNode: public BinaryOperationNode
		{
		public:
			XorNode( Cedomp::Type::TypeCode type, ExpressionNode* lhs,
					ExpressionNode* rhs );
		protected:
			virtual void printOpName() const;
		};

		class UnaryOperationNode: public ExpressionNode
		{
		public:
			UnaryOperationNode( Cedomp::Type::TypeCode type,
					ExpressionNode* expr );
		protected:
			virtual void printExpressionValue() const;
			virtual void printOpName() const = 0;
			std::unique_ptr<ExpressionNode> expr;
		};

		class UnaryMinusNode: public UnaryOperationNode
		{
		public:
			UnaryMinusNode( Cedomp::Type::TypeCode type, ExpressionNode* expr );
		protected:
			virtual void printOpName() const;
		};

		class NotNode: public UnaryOperationNode
		{
		public:
			NotNode( Cedomp::Type::TypeCode type, ExpressionNode* expr );
		protected:
			virtual void printOpName() const;
		};

		class EmbracedExpression: public ExpressionNode
		{
		public:
			EmbracedExpression( ExpressionNode* exprNode );
			virtual void printExpressionValue() const;
		private:
			std::unique_ptr<ExpressionNode> exprNode;
		};

	}
}
#endif /* EXPRESSIONNODE_H_ */
