/*
 * TypeExceptions.cpp
 *
 *  Created on: Jul 7, 2016
 *      Author: mitthy
 */
#include "Type/Types.h"
#include "Exceptions/TypeExceptions.h"

using namespace Cedomp::Exceptions;
using namespace Cedomp::Type;

IncompatibleTypeException::IncompatibleTypeException( const TypeCode& type1,
		const TypeCode& type2 ): typeCode1(type1), typeCode2(type2)
{

}

std::string IncompatibleTypeException::Error()
{
	std::string typeNameLeft = Type::Type::getTypeName(typeCode1);
	std::string typeNameRight = Type::Type::getTypeName(typeCode2);
	std::string result = "incompatible type: ";
	result += typeNameLeft;
	result += " ";
	result += typeNameRight;
	return result;
}
