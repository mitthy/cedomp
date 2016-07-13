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
#include "Scope/Scope.h"
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
			Cedomp::Scope::ScopeNode* scope;
		};

		class AssignBlockNode: public AbstractNode
		{
		public:
			void addNode( AssignVariableNode* node );
			virtual void printNode() const;
		private:
			std::vector<std::unique_ptr<AssignVariableNode>> nodes;
		};

		class IfNode: public StatementNode
		{
		public:
			IfNode( ExpressionNode* condition );
			IfNode( ExpressionNode* condition, BlockNode* thenBody );
			IfNode( ExpressionNode* condition, BlockNode* thenBody,
					BlockNode* elseBody );
			virtual void printNode() const;
			virtual void searchReturnValue(
					std::vector<ExpressionNode*>& output ) const;
		private:
			std::unique_ptr<ExpressionNode> condition;
			std::unique_ptr<BlockNode> thenBody;
			std::unique_ptr<BlockNode> elseBody;
		};

		class WhileNode: public StatementNode
		{
		public:
			WhileNode( ExpressionNode* condition, BlockNode* body );
			virtual void printNode() const;
			virtual void searchReturnValue(
					std::vector<ExpressionNode*>& output ) const;
		private:
			std::unique_ptr<ExpressionNode> condition;
			std::unique_ptr<BlockNode> body;
		};

		class FunctionNode: public StatementNode
		{
		public:
			FunctionNode( std::string id,
					std::vector<Cedomp::AST::ExpressionNode*>* args,
					Cedomp::Type::TypeCode returnType,
					Cedomp::Type::TypeCode genericType, BlockNode* body );
			virtual void printNode() const;
		private:
			std::string id;
			std::vector<std::shared_ptr<Cedomp::AST::ExpressionNode>> args;
			Cedomp::Type::TypeCode returnType;
			Cedomp::Type::TypeCode genericType;
			BlockNode* body;
		};

		class ReturnNode: public StatementNode
		{
		public:
			ReturnNode( ExpressionNode* expr );
			virtual void printNode() const;
			virtual void searchReturnValue(
					std::vector<ExpressionNode*>& output ) const;
		private:
			std::unique_ptr<ExpressionNode> retValue;
		};

	}
}

#endif /* STATEMENTNODE_H_ */
