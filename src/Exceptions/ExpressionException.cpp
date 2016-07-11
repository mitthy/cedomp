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
	std::string result = "Variable ";
	result += varName;
	result += " was not declared so can't be indexed";
	return result;
}

VariableNotDeclaredException::VariableNotDeclaredException(
		const std::string& id ) :
		varName(id)
{

}
std::string VariableNotDeclaredException::Error()
{
	std::string result = "Computing expression: variable ";
	result += varName;
	result += " was not declared.";
	return result;
}

BinaryOperationNotSupported::BinaryOperationNotSupported(
		const std::string& opName, Cedomp::Type::TypeCode type,
		Cedomp::Type::TypeCode type2 ) :
		opName(opName), typeLeft(type), typeRight(type2)
{

}

std::string BinaryOperationNotSupported::Error()
{
	std::string result = "Operation ";

	auto typeNameLeft = Cedomp::Type::Type::getTypeName(typeLeft);
	auto typeNameRight = Cedomp::Type::Type::getTypeName(typeRight);
	result += typeNameLeft;
	result += " ";
	result += opName;
	result += " ";
	result += typeNameRight;
	result += " not supported";
	return result;
}
