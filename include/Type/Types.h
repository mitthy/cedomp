/*
 * Types.h
 *
 *  Created on: Jul 7, 2016
 *      Author: mitthy
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <string>
#include <map>
#include <set>

/**
 * TODO: Add set of supported operations for each type.
 */

namespace Cedomp
{
	namespace Type
	{

		typedef unsigned long TypeCode;

		/////////////////////////////////////////////////////////////////////////////////////////////
		//Change BaseType to be read from a file. Changes to the initialization of the static members
		//should be made accordingly
		/////////////////////////////////////////////////////////////////////////////////////////////

		/**
		 * Should this enumeration be modified to add more base types to the language, it should
		 * always end with TEND
		 */
		enum BaseType
		{
			TYPEERROR,
			TYPEINT,
			TYPEFLOAT,
			TYPEBOOL,
			TYPEFUNCTION,
			TYPEMAP,
			TYPELIST,
			TYPESTRING,
			TYPEGENERIC,
			TYPEDYNAMIC,
			TEND
		};

		class Type
		{
		public:

			/**
			 * Receives a string as input and output its type code.
			 * Useful for translating strings to type codes.
			 *
			 * @param typeName		The name of the type
			 *
			 * @return				The code used to represent the type.
			 *
			 */
			static TypeCode getTypeCode( const std::string& typeName );

			/**
			 * This function is used to register an user defined type to a type code.
			 *
			 * @param typeName		The name of the type
			 *
			 * @return 				The code used to represent the type
			 *
			 */
			static void registerType( const std::string& typeName );

			/**
			 * This function is used for coercion purpose. If typeCode1 is compatible with
			 * typeCode2, they can be used in the same place.
			 *
			 * @param typeCode1 	The code of the first type
			 *
			 * @param typeCode2 	The code of the second type
			 */
			static void registerCompatible( const TypeCode& typeCode1,
					const TypeCode& typeCode2 );

			/**
			 * Returns if typeCode1 is compatible with typeCode2.
			 *
			 * @param typeCode1		The code of the first type
			 *
			 * @param typeCode2		The code of the second type
			 *
			 * @return				true if compatible false otherwise.
			 */
			static bool isCompatible( const TypeCode& typeCode1,
					const TypeCode& typeCode2 );

			static bool isBaseType( const TypeCode& typeCode );

			static std::string getTypeName( const TypeCode& typeCode );

		private:

			static std::set<std::string> typeName;

			static std::map<TypeCode, std::string> typeMap;

			static std::map<TypeCode, std::set<TypeCode>> compatibilityMap;

			//Last should always be initialized to TEND
			static TypeCode last;

		};

	}
}

#endif /* TYPES_H_ */
