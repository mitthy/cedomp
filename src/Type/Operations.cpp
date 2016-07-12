/*
 * Operations.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: mitthy
 */

#include "Type/Operations.h"

using namespace Cedomp::Type;

Operation& Operation::getInstance()
{
	static Operation op;
	return op;
}

void Operation::registerBinaryOperation( TypeCode type1,
		const std::string& operation, TypeCode type2, TypeCode returnType )
{
	if (binaryOpMap.find(type1) == binaryOpMap.end())
	{
		binaryOpMap[type1] =
				std::map<std::string, std::map<TypeCode, TypeCode>>();
	}
	if (binaryOpMap[type1].find(operation) == binaryOpMap[type1].end())
	{
		binaryOpMap[type1][operation] = std::map<TypeCode, TypeCode>();
	}
	if (binaryOpMap[type1][operation].find(type2)
			== binaryOpMap[type1][operation].end())
	{
		binaryOpMap[type1][operation][type2] = returnType;
	}
}
std::map<TypeCode, std::map<std::string, TypeCode>> unaryOpMap;
void Operation::registerUnaryOperation( TypeCode type,
		const std::string& operation, TypeCode ret )
{
	if (unaryOpMap.find(type) == unaryOpMap.end())
	{
		unaryOpMap[type] = std::map<std::string, TypeCode>();
	}
	if (unaryOpMap[type].find(operation) == unaryOpMap[type].end())
	{
		unaryOpMap[type][operation] = ret;
	}
}

bool Operation::getReturnBinaryType( TypeCode type1,
		const std::string& operation, TypeCode type2, TypeCode& ret )
{
	if (this->binaryOpMap.find(type1) == binaryOpMap.end())
	{
		ret = BaseType::TYPEERROR;
		return false;
	}
	auto secondCheck = binaryOpMap[type1];
	if (secondCheck.find(operation) == secondCheck.end())
	{
		ret = BaseType::TYPEERROR;
		return false;
	}
	auto thirdCheck = secondCheck[operation];
	if (thirdCheck.find(type2) == thirdCheck.end())
	{
		ret = BaseType::TYPEERROR;
		return false;
	}
	ret = thirdCheck[type2];
	return true;
}

bool Operation::getReturnUnaryType( TypeCode type, const std::string& operation,
		TypeCode& ret )
{
	if (this->unaryOpMap.find(type) == this->unaryOpMap.end())
	{
		ret = BaseType::TYPEERROR;
		return false;
	}
	auto secondCheck = unaryOpMap[type];
	if (secondCheck.find(operation) == secondCheck.end())
	{
		ret = BaseType::TYPEERROR;
		return false;
	}
	ret = secondCheck[operation];
	return true;
}

Operation::Operation()
{
	initializeBinaryOpMap();
	initializeUnaryOpMap();
}

void Operation::initializeBinaryOpMap()
{
	//INTEGER
	registerBinaryOperation(BaseType::TYPEINT, "+", BaseType::TYPEINT,
			BaseType::TYPEINT);
	registerBinaryOperation(BaseType::TYPEINT, "-", BaseType::TYPEINT,
			BaseType::TYPEINT);
	registerBinaryOperation(BaseType::TYPEINT, "*", BaseType::TYPEINT,
			BaseType::TYPEINT);
	registerBinaryOperation(BaseType::TYPEINT, "/", BaseType::TYPEINT,
			BaseType::TYPEINT);
	registerBinaryOperation(BaseType::TYPEINT, "+=", BaseType::TYPEINT,
			BaseType::TYPEINT);
	registerBinaryOperation(BaseType::TYPEINT, "-=", BaseType::TYPEINT,
			BaseType::TYPEINT);
	registerBinaryOperation(BaseType::TYPEINT, "*=", BaseType::TYPEINT,
			BaseType::TYPEINT);
	registerBinaryOperation(BaseType::TYPEINT, "/=", BaseType::TYPEINT,
			BaseType::TYPEINT);
	registerBinaryOperation(BaseType::TYPEINT, "mod", BaseType::TYPEINT,
			BaseType::TYPEINT);
	registerBinaryOperation(BaseType::TYPEINT, "mod=", BaseType::TYPEINT,
			BaseType::TYPEINT);
	registerBinaryOperation(BaseType::TYPEINT, ">", BaseType::TYPEINT,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPEINT, "<", BaseType::TYPEINT,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPEINT, "!=", BaseType::TYPEINT,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPEINT, "==", BaseType::TYPEINT,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPEINT, ">=", BaseType::TYPEINT,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPEINT, "<=", BaseType::TYPEINT,
			BaseType::TYPEBOOL);

	//FLOAT

	registerBinaryOperation(BaseType::TYPEFLOAT, "+", BaseType::TYPEFLOAT,
			BaseType::TYPEFLOAT);
	registerBinaryOperation(BaseType::TYPEFLOAT, "-", BaseType::TYPEFLOAT,
			BaseType::TYPEFLOAT);
	registerBinaryOperation(BaseType::TYPEFLOAT, "*", BaseType::TYPEFLOAT,
			BaseType::TYPEFLOAT);
	registerBinaryOperation(BaseType::TYPEFLOAT, "/", BaseType::TYPEFLOAT,
			BaseType::TYPEFLOAT);
	registerBinaryOperation(BaseType::TYPEFLOAT, "+=", BaseType::TYPEFLOAT,
			BaseType::TYPEFLOAT);
	registerBinaryOperation(BaseType::TYPEFLOAT, "-=", BaseType::TYPEFLOAT,
			BaseType::TYPEFLOAT);
	registerBinaryOperation(BaseType::TYPEFLOAT, "*=", BaseType::TYPEFLOAT,
			BaseType::TYPEFLOAT);
	registerBinaryOperation(BaseType::TYPEFLOAT, "/=", BaseType::TYPEFLOAT,
			BaseType::TYPEFLOAT);
	registerBinaryOperation(BaseType::TYPEFLOAT, ">", BaseType::TYPEFLOAT,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPEFLOAT, "<", BaseType::TYPEFLOAT,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPEFLOAT, "!=", BaseType::TYPEFLOAT,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPEFLOAT, "==", BaseType::TYPEFLOAT,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPEFLOAT, ">=", BaseType::TYPEFLOAT,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPEFLOAT, "<=", BaseType::TYPEFLOAT,
			BaseType::TYPEBOOL);

	//BOOL

	registerBinaryOperation(BaseType::TYPEBOOL, "and", BaseType::TYPEBOOL,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPEBOOL, "or", BaseType::TYPEBOOL,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPEBOOL, "xor", BaseType::TYPEBOOL,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPEBOOL, "==", BaseType::TYPEBOOL,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPEBOOL, "!=", BaseType::TYPEBOOL,
			BaseType::TYPEBOOL);

	//STRING

	registerBinaryOperation(BaseType::TYPESTRING, "+", BaseType::TYPESTRING,
			BaseType::TYPESTRING);
	registerBinaryOperation(BaseType::TYPESTRING, "+=", BaseType::TYPESTRING,
			BaseType::TYPESTRING);
	registerBinaryOperation(BaseType::TYPESTRING, "[]", BaseType::TYPEINT,
			BaseType::TYPESTRING);
	registerBinaryOperation(BaseType::TYPESTRING, ">", BaseType::TYPESTRING,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPESTRING, ">=", BaseType::TYPESTRING,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPESTRING, "<", BaseType::TYPESTRING,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPESTRING, "<=", BaseType::TYPESTRING,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPESTRING, "==", BaseType::TYPESTRING,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPESTRING, "!=", BaseType::TYPESTRING,
			BaseType::TYPEBOOL);
	registerBinaryOperation(BaseType::TYPESTRING, "-", BaseType::TYPEINT,
			BaseType::TYPESTRING);
	registerBinaryOperation(BaseType::TYPESTRING, "-=", BaseType::TYPEINT,
			BaseType::TYPESTRING);

	//MAP

	registerBinaryOperation(BaseType::TYPEMAP, "[]", BaseType::TYPESTRING,
			BaseType::TYPEGENERIC);
	registerBinaryOperation(BaseType::TYPEMAP, "-", BaseType::TYPESTRING,
			BaseType::TYPEMAP);
	registerBinaryOperation(BaseType::TYPEMAP, "-=", BaseType::TYPESTRING,
			BaseType::TYPEMAP);

	//LIST

	registerBinaryOperation(BaseType::TYPELIST, "[]", BaseType::TYPEINT,
			BaseType::TYPEGENERIC);
	registerBinaryOperation(BaseType::TYPELIST, "-", BaseType::TYPEINT,
			BaseType::TYPELIST);
	registerBinaryOperation(BaseType::TYPELIST, "-=", BaseType::TYPEINT,
			BaseType::TYPELIST);
	registerBinaryOperation(BaseType::TYPELIST, "+=", BaseType::TYPEGENERIC,
			BaseType::TYPELIST);
	registerBinaryOperation(BaseType::TYPELIST, "+", BaseType::TYPEGENERIC,
			BaseType::TYPELIST);

}

void Operation::initializeUnaryOpMap()
{
	registerUnaryOperation(BaseType::TYPEBOOL, "not", BaseType::TYPEBOOL);
	registerUnaryOperation(BaseType::TYPEFUNCTION, "()", BaseType::TYPEGENERIC);
	registerUnaryOperation(BaseType::TYPEINT, "-", BaseType::TYPEINT);
	registerUnaryOperation(BaseType::TYPEFLOAT, "-", BaseType::TYPEFLOAT);
}
