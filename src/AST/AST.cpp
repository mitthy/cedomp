/*
 * AST.cpp
 *
 *  Created on: Jul 7, 2016
 *      Author: mitthy
 */
#include "AST/AST.h"
#include "Type/Types.h"

using namespace Cedomp::Type;
using namespace Cedomp::AST;

TypeCode ExpressionNode::getTypeCode()
{
	return type;
}

AssignVariableNode::AssignVariableNode( std::string string,
		ExpressionNode* expr )
{

}
