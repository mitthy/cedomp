/*
 * VarAssignExceptions.cpp
 *
 *  Created on: Jul 7, 2016
 *      Author: mitthy
 */

#include "Exceptions/VarAssignExceptions.h"
#include <string>
using namespace Cedomp::Exceptions;

FunctionAsVariable::FunctionAsVariable( const std::string& funcName ) :
		varName(funcName)
{
}

std::string FunctionAsVariable::Error()
{
	std::string result = "Using function ";
	result += varName;
	result += " as variable";
	return result;
}

WrongVarNumberException::WrongVarNumberException( unsigned int varAmount,
		unsigned int exprAmount ) :
		varAmount(varAmount), exprAmount(exprAmount)
{
}

std::string WrongVarNumberException::Error()
{
	std::string varAmountStr = std::to_string(varAmount);
	std::string exprAmountStr = std::to_string(exprAmount);
	std::string result = "Assigning ";
	result += exprAmountStr;
	result += " expressions to ";
	result += varAmountStr;
	result += " variables";
	return result;
}

IndexNotSupportedException::IndexNotSupportedException(
		const std::string& varName ) :
		varName(varName)
{
}

std::string IndexNotSupportedException::Error()
{
	std::string result = "Variable ";
	result += varName;
	result += " can't be indexed";
	return result;
}

