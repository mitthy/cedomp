/*
 * CedompException.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: mitthy
 */
#include "Exceptions/CedompException.h"
#include <string>
extern void yyerror(const char* s, ...);
using namespace Cedomp::Exceptions;

void CedompException::PrintSemanticError()
{
	std::string cause = Error();
	yyerror(cause.c_str());
}

