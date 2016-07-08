/*
 * TypeException.h
 *
 *  Created on: Jul 7, 2016
 *      Author: mitthy
 */

#ifndef TYPEEXCEPTION_H_
#define TYPEEXCEPTION_H_
#include <exception>
#include "Type/Types.h"

namespace Cedomp
{
	namespace Exceptions
	{
		class TypeException: public std::exception
		{

		};

		class IncompatibleTypeException: public TypeException
		{
		public:
			IncompatibleTypeException( const Type::TypeCode& type1,
					const Type::TypeCode& type2 );
		};
	}
}

#endif /* TYPEEXCEPTION_H_ */
