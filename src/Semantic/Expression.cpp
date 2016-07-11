/*
 * Expression.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: mitthy
 */
#include "Semantic/Expression.h"
#include "AST/AST.h"
#include <memory>
#include "Scope/Scope.h"
#include "Exceptions/ExpressionExceptions.h"


using namespace Cedomp::AST;

using namespace Cedomp::Exceptions;

ExpressionNode* Cedomp::Semantic::ComputeInteger( long * val )
{
	return new ::IntegerNode(val);
}

ExpressionNode* Cedomp::Semantic::ComputeFloat( double* val )
{
	return new ::FloatNode(val);
}

ExpressionNode* Cedomp::Semantic::ComputeBool( bool * val )
{
	return new ::BoolNode(val);
}

ExpressionNode* Cedomp::Semantic::ComputeID( char * val )
{
	std::string id(val);
	auto& varScope = Cedomp::Scope::Scope::getScope();
	auto& funScope = Cedomp::Scope::FunctionScope::getScope();
	if(funScope.searchScope(id))
	{
		return new VariableNode(id, Type::BaseType::TYPEFUNCTION);
	}
	else if(varScope.searchScope(id))
	{
		return new VariableNode(id, varScope.searchScope(id)->type);
	}
	else
	{
		throw VariableNotDeclaredException(id);
	}

}

ExpressionNode* Cedomp::Semantic::ComputeString( std::string * val )
{
	return new StringNode(val);
}

ExpressionNode* Cedomp::Semantic::ComputeMap( std::map<std::string, void*>* val )
{
	return new MapNode(val);
}

ExpressionNode* Cedomp::Semantic::ComputeList( std::vector<void*>* val )
{

}

ExpressionNode* Cedomp::Semantic::ComputeIndex( char * id, ExpressionNode* val )
{

}

ExpressionNode* Cedomp::Semantic::ComputeMod( ExpressionNode* left,
		ExpressionNode* right )
{

}

ExpressionNode* Cedomp::Semantic::ComputeAddition( ExpressionNode* left,
		ExpressionNode* right )
{

}

ExpressionNode* Cedomp::Semantic::ComputeSubtraction( ExpressionNode* left,
		ExpressionNode* right )
{

}

ExpressionNode* Cedomp::Semantic::ComputeMultiplication( ExpressionNode* left,
		ExpressionNode* right )
{

}

ExpressionNode* Cedomp::Semantic::ComputeDivision( ExpressionNode* left,
		ExpressionNode* right )
{

}

ExpressionNode* Cedomp::Semantic::ComputeUnaryMinus( ::ExpressionNode* val )
{

}

ExpressionNode* Cedomp::Semantic::ComputeGreaterThan( ExpressionNode* left,
		ExpressionNode* right )
{

}

ExpressionNode* Cedomp::Semantic::ComputeEquals( ExpressionNode* left,
		ExpressionNode* right )
{

}

ExpressionNode* Cedomp::Semantic::ComputeDifferent( ExpressionNode* left,
		ExpressionNode* right )
{

}

ExpressionNode* Cedomp::Semantic::ComputeGreaterEquals( ExpressionNode* left,
		ExpressionNode* right )
{

}

ExpressionNode* Cedomp::Semantic::ComputeAnd( ExpressionNode* left,
		ExpressionNode* right )
{

}

ExpressionNode* Cedomp::Semantic::ComputeXor( ExpressionNode* left,
		ExpressionNode* right )
{

}

ExpressionNode* Cedomp::Semantic::ComputeOr( ExpressionNode* left,
		ExpressionNode* right )
{

}

ExpressionNode* Cedomp::Semantic::ComputeNot( ExpressionNode* val )
{

}

ExpressionNode* Cedomp::Semantic::ComputeLessEqual( ExpressionNode* left,
		ExpressionNode* right )
{

}

ExpressionNode* Cedomp::Semantic::ComputeLess( ExpressionNode* left,
		ExpressionNode* right )
{

}

ExpressionNode* Cedomp::Semantic::ComputeEnclosed( ExpressionNode* val )
{

}
