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
std::map<std::string, TypeCode> createTypeMap()
{
	std::map<std::string, TypeCode> ret;
	ret["integer"] = BaseType::TYPEINT;
	ret["float"] = BaseType::TYPEFLOAT;
	ret["bool"] = BaseType::TYPEBOOL;
	ret["function"] = BaseType::TYPEFUNCTION;
	ret["map"] = BaseType::TYPEMAP;
	ret["list"] = BaseType::TYPELIST;
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
	return ret;
}

std::map<std::string, TypeCode> Type::typeMap = createTypeMap();

std::map<TypeCode, std::set<TypeCode>> Type::compatibilityMap =
		createCompatibilityMap();

TypeCode Type::getTypeCode( const std::string& typeName )
{
	if (typeMap.find(typeName) == typeMap.end())
	{
		return BaseType::TYPEERROR;
	}
	return typeMap[typeName];

}

void Type::registerType( const std::string& typeName )
{
	typeMap[typeName] = ++last;
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
