/*
 * Scope.h
 *
 *  Created on: May 13, 2016
 *      Author: mitthy
 */

#ifndef SCOPE_H_
#define SCOPE_H_
#include "Type/Types.h"
#include "AST/BasicNode.h"
#include "AST/ExpressionNode.h"
#include <map>
#include <string>
#include <vector>

namespace Cedomp
{
	namespace Scope
	{

		struct variableInfo
		{
			Type::TypeCode type;
			Type::TypeCode genericType;
			bool globalScope;
			variableInfo();
		};

		struct functionInfo
		{
			bool defined;
			Type::TypeCode type;
			std::vector<variableInfo> argInfo;
		};

		class ScopeNode
		{
		public:
			ScopeNode( ScopeNode* previous );
			bool searchScope( const std::string& name,
					variableInfo** outputInfo );
			bool searchCurrentScope( const std::string& varName,
					variableInfo** outputInfo );
			void addToScope( const std::string& name,
					const Type::TypeCode& varType );
			ScopeNode* previousNode();
			ScopeNode( const ScopeNode& rhs ) = delete;
			ScopeNode& operator=( const ScopeNode& rhs ) = delete;
			void generateScope( ScopeNode** curentScope );
			void destroyScope( ScopeNode** currentScope );
			variableInfo* searchScope( const std::string& varName );
			~ScopeNode();
		private:
			ScopeNode* previous;
			std::vector<ScopeNode*> children;
			std::map<std::string, variableInfo> variableValMap;
		};

		class Scope
		{
		public:
			static Scope& getScope();
			Scope( const Scope& rhs ) = delete;
			Scope& operator=( const Scope& rhs ) = delete;
			void addToScope( const std::string& name,
					const Type::TypeCode& varType );
			~Scope();
			void generateScope();
			variableInfo* searchScope( const std::string& varName );
			variableInfo* searchCurrentScope( const std::string& varName );
			bool deleteScope();
			ScopeNode* getCurrentScope();

		private:
			Scope();
			ScopeNode* globalScope;
			ScopeNode* tail;
		};

		class FunctionScopeNode
		{
		public:
			FunctionScopeNode( FunctionScopeNode* previous );
			bool searchScope( const std::string& name,
					functionInfo** outputInfo );
			bool searchCurrentScope( const std::string& varName,
					functionInfo** outputInfo );
			void addToScope( const std::string& name,
					const Type::TypeCode& varType );
			FunctionScopeNode* previousNode();
			FunctionScopeNode( const FunctionScopeNode& rhs ) = delete;
			FunctionScopeNode& operator=( const FunctionScopeNode& rhs ) = delete;
			void generateScope( FunctionScopeNode** curentScope );
			void destroyScope( FunctionScopeNode** currentScope );
			functionInfo* searchScope( const std::string& varName );
			~FunctionScopeNode();
		private:
			FunctionScopeNode* previous;
			std::vector<FunctionScopeNode*> children;
			std::map<std::string, functionInfo> functionValMap;
		};

		class FunctionScope
		{
		public:
			static FunctionScope& getScope();
			FunctionScope( const FunctionScope& rhs ) = delete;
			Scope& operator=( const FunctionScope& rhs ) = delete;
			void addToScope( const std::string& name,
					const Type::TypeCode& varType );
			~FunctionScope();
			void generateScope();
			functionInfo* searchScope( const std::string& varName );
			functionInfo* searchCurrentScope( const std::string& varName );
			bool deleteScope();
			FunctionScopeNode* getCurrentScope();
		private:
			FunctionScope();
			FunctionScopeNode* globalScope;
			FunctionScopeNode* tail;
		};

	}
}
#endif /* SCOPE_H_ */
