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
	std::string result = "using function ";
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
	std::string result = "assigning ";
	result += exprAmountStr;
	result += " to ";
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
	std::string result = "variable ";
	result += varName;
	result += " can't be indexed";
	return result;
}

VariableNotDeclaredException::VariableNotDeclaredException(
		const std::string& varName ) :
		varName(varName)
{
}

std::string VariableNotDeclaredException::Error()
{
	std::string result = "variable ";
	result += varName;
	result += " was not declared so can't be indexed";
	return result;
}
