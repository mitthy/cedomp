/*
 * Utility.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: mitthy
 */

#include "Semantic/Utility.h"
#include "Scope/Scope.h"

void Cedomp::Semantic::CreateScope()
{
	Cedomp::Scope::Scope::getScope().generateScope();
	Cedomp::Scope::FunctionScope::getScope().generateScope();
	//Change to include function scope later
}


void Cedomp::Semantic::DestroyScope()
{
	Cedomp::Scope::Scope::getScope().deleteScope();
	Cedomp::Scope::FunctionScope::getScope().deleteScope();
	//Change to include function scope later
}

