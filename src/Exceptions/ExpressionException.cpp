/*
 * ExpressionException.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: mitthy
 */
#include "Exceptions/ExpressionExceptions.h"

using namespace Cedomp::Exceptions;

VariableNotDeclaredIndexedException::VariableNotDeclaredIndexedException(
		const std::string& varName ) :
		varName(varName)
{
}

std::string VariableNotDeclaredIndexedException::Error()
{
	std::string result = "variable ";
	result += varName;
	result += " was not declared so can't be indexed";
	return result;
}

VariableNotDeclaredException::VariableNotDeclaredException(
		const std::string& id ): varName(id)
{

}
std::string VariableNotDeclaredException::Error()
{
	std::string result = "Error computing expression: variable ";
	result += varName;
	result += " was not declared.";
	return result;
}
