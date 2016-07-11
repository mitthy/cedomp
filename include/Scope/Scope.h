/*
 * Scope.h
 *
 *  Created on: May 13, 2016
 *      Author: mitthy
 */

#ifndef SCOPE_H_
#define SCOPE_H_
#include "Type/Types.h"
#include "AST/AST.h"
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
			~ScopeNode() = default;
		private:
			ScopeNode* previous;
			std::map<std::string, variableInfo> variableValMap;
		};

		class Scope
		{
		public:
			static Scope& getScope();
			Scope( const Scope& rhs ) = delete;
			Scope& operator=( const Scope& rhs ) = delete;
			void addToScope( const std::string& name,
					const Type::TypeCode& varType);
			~Scope();
			void generateScope();
			variableInfo* searchScope( const std::string& varName );
			variableInfo* searchCurrentScope( const std::string& varName );
			bool deleteScope();
		private:
			Scope();
			ScopeNode* globalScope;
			ScopeNode* tail;
		};

		class FunctionScope
		{
		public:
			static FunctionScope& getScope();
			FunctionScope( const FunctionScope& rhs ) = delete;
			FunctionScope& operator=( const FunctionScope& rhs ) = delete;
			void addToScope( const std::string& name,
					const Type::TypeCode& varType,
					std::vector<AST::VariableNode*> args );
			~FunctionScope();
			functionInfo* searchScope( const std::string& funcName );
			std::map<std::string, functionInfo>::iterator begin();
			std::map<std::string, functionInfo>::iterator end();
		private:
			FunctionScope();
			std::map<std::string, functionInfo> functionValMap;

		};

	}
}
#endif /* SCOPE_H_ */
