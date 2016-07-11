/*
 * Statement.h
 *
 *  Created on: Jul 10, 2016
 *      Author: mitthy
 */

#ifndef STATEMENT_H_
#define STATEMENT_H_
#include <vector>
#include "AST/AST.h"
namespace Cedomp
{
	namespace Semantic
	{

		AST::AbstractNode * AssignVariableStatement(std::vector<AST::AssignVariableNode*>*);

		AST::BlockNode* AddStatement(AST::BlockNode* block, AST::AbstractNode* statement);

	}
}


#endif /* STATEMENT_H_ */
