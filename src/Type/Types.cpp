/*
 * Types.cpp
 *
 *  Created on: Jul 7, 2016
 *      Author: mitthy
 */
#include "Type/Types.h"

using namespace Cedomp::Type;

TypeCode Type::last = BaseType::TEND;

/**
 * This should be altered everytime a new base time is introduced to the language
 */
std::set<std::string> createTypeSet()
{
	std::set<std::string> ret;
	ret.insert("integer");
	ret.insert("float");
	ret.insert("bool");
	ret.insert("function");
	ret.insert("map");
	ret.insert("list");
	ret.insert("string");
	ret.insert("generic");
	ret.insert("dynamic");
	return ret;
}

/**
 * This should be altered everytime a new base time is introduced to the language
 */


std::map<TypeCode, std::string> createTypeMap()
{
	std::map<TypeCode, std::string> ret;
	ret[TYPEINT] = "integer";
	ret[TYPEFLOAT] = "float";
	ret[TYPEBOOL] = "bool";
	ret[TYPEFUNCTION] = "function";
	ret[TYPEMAP] = "map";
	ret[TYPELIST] = "list";
	ret[TYPESTRING] = "string";
	ret[TYPEGENERIC] = "generic";
	ret[TYPEDYNAMIC] = "dynamic";
	return ret;
}

/**
 * This should be altered everytime a new base time is introduced to the language.
 * Change it to change the base compatibility of the base types.
 */
std::map<TypeCode, std::set<TypeCode>> createCompatibilityMap()
{
	std::map<TypeCode, std::set<TypeCode>> ret;
	for (TypeCode i = TYPEERROR + 1; i < TEND; ++i)
	{
		ret[i] = std::set<TypeCode>();
	}
	ret[TYPEINT].insert(TYPEFLOAT);
	ret[TYPEFLOAT].insert(TYPEINT);
	ret[TYPEBOOL].insert(TYPEINT);
	ret[TYPESTRING].insert(TYPEBOOL);
	ret[TYPESTRING].insert(TYPEINT);
	ret[TYPESTRING].insert(TYPEFLOAT);
	return ret;
}

std::map<TypeCode, std::string> Type::typeMap = createTypeMap();

std::map<TypeCode, std::set<TypeCode>> Type::compatibilityMap =
		createCompatibilityMap();

std::set<std::string> Type::typeName = createTypeSet();

TypeCode Type::getTypeCode( const std::string& typeName )
{
	for(const auto& pair : typeMap)
	{
		if(pair.second == typeName)
		{
			return pair.first;
		}
	}
	return BaseType::TYPEERROR;

}

void Type::registerType( const std::string& typeName )
{
	if (Type::typeName.find(typeName) == Type::typeName.end())
	{
		typeMap[++last] = typeName;
		compatibilityMap[last] = std::set<TypeCode>();
	}
}

void Type::registerCompatible( const TypeCode& typeCode1,
		const TypeCode& typeCode2 )
{
	if (typeCode1 != typeCode2)
	{
		compatibilityMap[typeCode1].insert(typeCode2);
	}
}

bool Type::isCompatible( const TypeCode& typeCode1, const TypeCode& typeCode2 )
{
	if (typeCode1 == BaseType::TYPEERROR || typeCode2 == BaseType::TYPEERROR)
	{
		return false;
	}
	if(typeCode1 == BaseType::TYPEDYNAMIC || typeCode2 == BaseType::TYPEDYNAMIC)
	{
		return true;
	}
	if (typeCode1 == typeCode2)
	{
		return true;
	}
	if (compatibilityMap[typeCode1].find(typeCode2)
			== compatibilityMap[typeCode1].end())
	{
		return false;
	}
	return true;
}

bool Type::isBaseType( const TypeCode& typeCode )
{
	return typeCode > BaseType::TYPEERROR && typeCode < BaseType::TEND;
}

std::string Type::getTypeName( const TypeCode& typeCode )
{
	if(typeCode == BaseType::TYPEERROR || typeMap.find(typeCode) == typeMap.end())
	{
		return "unknown";
	}
	return typeMap[typeCode];
}
