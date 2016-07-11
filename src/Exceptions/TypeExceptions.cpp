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
		const TypeCode& type2 ) :
		typeCode1(type1), typeCode2(type2)
{

}

std::string IncompatibleTypeException::Error()
{
	std::string typeNameLeft = Type::Type::getTypeName(typeCode1);
	std::string typeNameRight = Type::Type::getTypeName(typeCode2);
	std::string result = "Incompatible type: ";
	result += typeNameLeft;
	result += " ";
	result += typeNameRight;
	return result;
}

IndexNotSupportedTypeException::IndexNotSupportedTypeException(
		std::string varName, Cedomp::Type::TypeCode typeId,
		Cedomp::Type::TypeCode typeIndex ) :
		varName(varName), typeId(typeId), typeIndex(typeIndex)
{

}

std::string IndexNotSupportedTypeException::Error()
{
	auto typeIDName = Cedomp::Type::Type::getTypeName(typeId);
	auto typeIndexName = Cedomp::Type::Type::getTypeName(typeIndex);
	std::string result = "Indexing var ";
	result += varName;
	result += ": type ";
	result += typeIDName;
	result += " can't be indexed with ";
	result += typeIndexName;
	return result;
}

ContainerTypeNotInitialized::ContainerTypeNotInitialized(
		const std::string& id ) :
		id(id)
{
}
std::string ContainerTypeNotInitialized::Error()
{
	std::string result = "Can't get value from container ";
	result += id;
	result += " because it was not initialized";
	return result;
}
