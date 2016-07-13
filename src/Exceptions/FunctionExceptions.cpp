/*
 * FunctionExceptions.cpp
 *
 *  Created on: Jul 12, 2016
 *      Author: mitthy
 */

#include "Exceptions/FunctionExceptions.h"
#include <string>
#include "Type/Types.h"
using namespace Cedomp::Exceptions;
std::string FunctionContextException::Error()
{
	return "can't declare function inside if or while context";
}

VariableAsFunction::VariableAsFunction( const std::string& id ) :
		id(id)
{
}

std::string VariableAsFunction::Error()
{
	std::string result = "can't declare ";
	result += id;
	result += " as a function: was already a variable";
	return result;
}

std::string ReturnOutsideFunction::Error()
{
	return "return declared outside of a function";
}

IncompatibleReturnType::IncompatibleReturnType()
{

}
std::string IncompatibleReturnType::Error()
{
	std::string result = "incompatible return type: ";
	return result;
}

RedeclarationOfFunction::RedeclarationOfFunction( const std::string& id ) :
		id(id)
{

}
std::string RedeclarationOfFunction::Error()
{
	return "redeclaration of function " + id;
}
